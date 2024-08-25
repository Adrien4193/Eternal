#include "WindowManager.h"

#include <cassert>
#include <format>
#include <stdexcept>

namespace
{
    using namespace Eternal;

    void On(const WindowRename &e, WindowPrivate &window)
    {
        window.Title = e.Title;
    }

    void On(const WindowMove &e, WindowPrivate &window)
    {
        window.Position = e.Position;
    }

    void On(const WindowResize &e, WindowPrivate &window)
    {
        window.Size = e.Size;
    }

    void On(const WindowClose &, WindowPrivate &)
    {
    }

    void On(const WindowInput &, WindowPrivate &)
    {
    }
}

namespace Eternal
{
    WindowManager::WindowManager(WindowHandleFactory handleFactory):
        m_HandleFactory(std::move(handleFactory))
    {
    }

    Window WindowManager::Add(const WindowSettings &settings)
    {
        auto handle = m_HandleFactory(settings);

        auto id = m_IdGenerator.Next();

        try
        {
            auto window = WindowPrivate{
                .Id = id,
                .Handle = std::move(handle),
                .Title = std::string(settings.Title),
                .Position = settings.Position,
                .Size = settings.Size,
            };

            auto [i, inserted] = m_Windows.emplace(id, std::move(window));
            assert(inserted);

            return Window(i->second);
        }
        catch (...)
        {
            m_IdGenerator.Recycle(id);
            throw;
        }
    }

    void WindowManager::Remove(Window window)
    {
        Remove(window.GetId());
    }

    void WindowManager::Remove(WindowId id)
    {
        auto i = m_Windows.find(id);

        if (i == m_Windows.end())
        {
            throw std::invalid_argument(std::format("Invalid window ID: {}", id));
        }

        m_Windows.erase(i);
        m_IdGenerator.Recycle(id);
    }

    void WindowManager::Poll()
    {
        for (auto &[id, window] : m_Windows)
        {
            auto messages = window.Handle.Poll();

            auto events = std::vector<WindowEvent>();

            for (const auto &message : messages)
            {
                if (const auto *event = std::get_if<WindowEvent>(&message))
                {
                    std::visit([&](const auto &e) { On(e, window); }, *event);
                    events.push_back(*event);
                }
            }

            window.Events = std::move(events);

            for (const auto &message : messages)
            {
                if (const auto *e = std::get_if<WindowException>(&message))
                {
                    throw *e;
                }
            }
        }
    }
}
