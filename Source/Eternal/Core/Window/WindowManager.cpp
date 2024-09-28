#include "WindowManager.h"

#include <cassert>
#include <format>
#include <stdexcept>

#include <Eternal/Core/Utils/Overload.h>

namespace Eternal
{
    WindowManager::WindowManager(WindowFactory handleFactory):
        m_Factory(std::move(handleFactory))
    {
    }

    Window WindowManager::Add(const WindowSettings &settings)
    {
        auto handle = m_Factory(settings);
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
            window.Events = window.Handle.Poll();

            for (const auto &event : window.Events)
            {
                std::visit(
                    Overload{
                        [&](const WindowRename &e) { window.Title = e.Title; },
                        [&](const WindowMove &e) { window.Position = e.Position; },
                        [&](const WindowResize &e) { window.Size = e.Size; },
                        [](const auto &) {},
                    },
                    event);
            }
        }
    }
}
