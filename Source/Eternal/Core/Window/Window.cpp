#include "Window.h"

namespace Eternal
{
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

    void WindowRef::Show()
    {
        m_Window->Handle.Show();
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
