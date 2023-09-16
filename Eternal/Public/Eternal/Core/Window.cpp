#include "Window.h"

namespace Eternal
{
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
