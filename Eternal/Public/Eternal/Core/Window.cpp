#include "Window.h"

namespace Eternal
{
    WindowPropertyListener::WindowPropertyListener(WindowProperties &properties):
        m_Properties(properties)
    {
    }

    void WindowPropertyListener::SetTitle(const std::string &title)
    {
        m_Properties.Title = title;
    }

    void WindowPropertyListener::Resize(const Vector2 &size)
    {
        m_Properties.Size = size;
    }

    void WindowPropertyListener::Close()
    {
        m_Properties.Closed = true;
    }

    Window::Window(WindowHandle &handle, WindowProperties &properties):
        m_Handle(handle),
        m_Properties(properties)
    {
    }

    void *Window::GetNativeHandle() const
    {
        return m_Handle.AsRawPtr();
    }

    const std::string &Window::GetTitle() const
    {
        return m_Properties.Title;
    }

    const Vector2 &Window::GetSize() const
    {
        return m_Properties.Size;
    }
}
