#include "Window.h"

namespace Eternal
{
    Window::Window(const WindowPrivate &window):
        m_Window(&window)
    {
    }

    WindowId Window::GetId() const
    {
        return m_Window->Id;
    }

    void *Window::GetNativeHandle() const
    {
        return m_Window->Handle.NativePtr;
    }

    std::span<const WindowEvent> Window::GetEvents() const
    {
        return m_Window->Events;
    }

    void Window::Show()
    {
        m_Window->Handle.Show();
    }

    std::string_view Window::GetTitle() const
    {
        return m_Window->Title;
    }

    void Window::SetTitle(std::string_view title)
    {
        m_Window->Handle.SetTitle(title);
    }

    Vector2 Window::GetPosition() const
    {
        return m_Window->Position;
    }

    void Window::SetPosition(Vector2 position)
    {
        m_Window->Handle.SetPosition(position);
    }

    Vector2 Window::GetSize() const
    {
        return m_Window->Size;
    }

    void Window::Resize(Vector2 size)
    {
        m_Window->Handle.Resize(size);
    }
}
