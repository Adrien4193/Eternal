#include "WindowManager.h"

#include <cassert>
#include <stdexcept>

namespace
{
    using namespace Eternal;

    WindowPrivate CreateWindowPrivate(WindowId id, WindowHandle handle, const WindowSettings &settings)
    {
        return WindowPrivate{
            .Id = id,
            .Handle = std::move(handle),
            .Title = std::string(settings.Title),
            .Position = settings.Position,
            .Size = settings.Size,
        };
    }

    WindowHolder CreateWindowHolder(WindowPrivate window)
    {
        auto windowPrivate = std::make_unique<WindowPrivate>(std::move(window));
        auto windowInterface = std::make_unique<Window>(*windowPrivate);
        return {
            .WindowPrivate = std::move(windowPrivate),
            .Window = std::move(windowInterface),
        };
    }

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

    void On(const WindowClose &e, WindowPrivate &window)
    {
        (void)e;
        (void)window;
    }

    void PollWindow(WindowPrivate &window)
    {
        auto events = window.Handle.Poll();
        for (const auto &event : events)
        {
            std::visit([&](const auto &e) { On(e, window); }, event);
        }
        window.Events = std::move(events);
    }
}

namespace Eternal
{
    WindowManagerPrivate::WindowManagerPrivate(WindowHandleFactory handleFactory):
        m_HandleFactory(std::move(handleFactory))
    {
    }

    Window &WindowManagerPrivate::AddWindow(const WindowSettings &settings)
    {
        auto handle = m_HandleFactory(settings);
        auto id = m_IdGenerator.Next();
        try
        {
            auto window = CreateWindowPrivate(id, std::move(handle), settings);
            auto holder = CreateWindowHolder(std::move(window));
            auto [i, inserted] = m_Windows.emplace(id, std::move(holder));
            assert(inserted);
            return *i->second.Window;
        }
        catch (...)
        {
            m_IdGenerator.Recycle(id);
            throw;
        }
    }

    void WindowManagerPrivate::RemoveWindow(WindowId id)
    {
        auto i = m_Windows.find(id);
        if (i == m_Windows.end())
        {
            throw std::invalid_argument("Invalid window ID");
        }
        m_Windows.erase(i);
        m_IdGenerator.Recycle(id);
    }

    void WindowManagerPrivate::PollWindows()
    {
        for (const auto &[id, holder] : m_Windows)
        {
            PollWindow(*holder.WindowPrivate);
        }
    }

    WindowManager::WindowManager(WindowManagerPrivate &windows):
        m_Windows(windows)
    {
    }

    Window &WindowManager::AddWindow(const WindowSettings &settings)
    {
        return m_Windows.AddWindow(settings);
    }

    void WindowManager::RemoveWindow(WindowId id)
    {
        m_Windows.RemoveWindow(id);
    }
}
