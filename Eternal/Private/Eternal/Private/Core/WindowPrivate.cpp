#include "WindowPrivate.h"

namespace Eternal
{
    WindowPrivate::WindowPrivate(std::unique_ptr<WindowHandle> handle, std::unique_ptr<WindowProperties> properties):
        m_Handle(std::move(handle)),
        m_Properties(std::move(properties))
    {
    }

    bool WindowPrivate::IsClosed() const
    {
        return m_Properties->Closed;
    }

    void WindowPrivate::Poll()
    {
        m_Handle->Poll();
    }
}
