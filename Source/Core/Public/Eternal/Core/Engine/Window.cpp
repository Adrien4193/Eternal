#include "Window.h"

namespace Eternal
{
    Window::Window(const WindowProperties &properties):
        m_Properties(properties)
    {
    }

    WindowId Window::GetId() const
    {
        return m_Properties.Id;
    }

    void *Window::GetNativeHandle() const
    {
        return m_Properties.NativeHandle;
    }

    const std::string &Window::GetTitle() const
    {
        return m_Properties.Title;
    }

    void Window::SetTitle(std::string_view title)
    {
        m_Properties.Send(WindowRename{title});
    }

    const Vector2 &Window::GetPosition() const
    {
        return m_Properties.Position;
    }

    void Window::SetPosition(const Vector2 &position)
    {
        return m_Properties.Send(WindowMove{position});
    }

    const Vector2 &Window::GetSize() const
    {
        return m_Properties.Size;
    }

    void Window::Resize(const Vector2 &size)
    {
        return m_Properties.Send(WindowResize{size});
    }
}
