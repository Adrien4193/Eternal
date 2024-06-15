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

    void On(const auto &e, WindowPrivate &window)
    {
        (void)e;
        (void)window;
    }
}

namespace Eternal
{
    WindowManager::WindowManager(WindowHandleFactory handleFactory):
        m_HandleFactory(std::move(handleFactory))
    {
    }

    WindowRef WindowManager::Add(const WindowSettings &settings)
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

            return WindowRef(i->second);
        }
        catch (...)
        {
            m_IdGenerator.Recycle(id);
            throw;
        }
    }

    void WindowManager::Remove(WindowRef window)
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
            auto events = window.Handle.Poll();

            for (const auto &event : events)
            {
                std::visit([&](const auto &e) { On(e, window); }, event);
            }

            window.Events = std::move(events);
        }
    }
}
