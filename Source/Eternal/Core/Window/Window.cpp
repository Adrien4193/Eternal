#include "Window.h"

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

    void On(const WindowClose &e, WindowPrivate &window)
    {
        (void)e;
        (void)window;
    }
}

namespace Eternal
{
    WindowPrivate CreateWindowPrivate(WindowId id, WindowHandle handle, const WindowSettings &settings)
    {
        return {
            .Id = id,
            .Handle = std::move(handle),
            .Title = std::string(settings.Title),
            .Position = settings.Position,
            .Size = settings.Size,
        };
    }

    void PollWindowPrivate(WindowPrivate &window)
    {
        auto events = window.Handle.Poll();
        for (const auto &event : events)
        {
            std::visit([&](const auto &e) { On(e, window); }, event);
        }
        window.Events = std::move(events);
    }

    WindowRef::WindowRef(const WindowPrivate &window):
        m_Window(&window)
    {
    }

    WindowId WindowRef::GetId() const
    {
        return m_Window->Id;
    }

    void *WindowRef::GetNativeHandle() const
    {
        return m_Window->Handle.NativePtr;
    }

    std::span<const WindowEvent> WindowRef::GetEvents() const
    {
        return m_Window->Events;
    }

    std::string_view WindowRef::GetTitle() const
    {
        return m_Window->Title;
    }

    void WindowRef::SetTitle(std::string_view title)
    {
        m_Window->Handle.SetTitle(title);
    }

    Vector2 WindowRef::GetPosition() const
    {
        return m_Window->Position;
    }

    void WindowRef::SetPosition(Vector2 position)
    {
        m_Window->Handle.SetPosition(position);
    }

    Vector2 WindowRef::GetSize() const
    {
        return m_Window->Size;
    }

    void WindowRef::Resize(Vector2 size)
    {
        m_Window->Handle.Resize(size);
    }
}
