#include "WindowPrivate.h"

#include <Eternal/Platform/NativeWindow.h>

namespace Eternal
{
    std::unique_ptr<WindowProperties> CreateWindowProperties(const WindowSettings &settings)
    {
        auto properties = std::make_unique<WindowProperties>();
        properties->Title = settings.Title;
        properties->Size = settings.Size;
        return properties;
    }

    WindowPropertyListener::WindowPropertyListener(WindowProperties &properties):
        m_Properties(properties)
    {
    }

    void WindowPropertyListener::OnSetTitle(const std::string &title)
    {
        m_Properties.Title = title;
    }

    void WindowPropertyListener::OnResize(const WindowSize &size)
    {
        m_Properties.Size = size;
    }

    void WindowPropertyListener::OnClose()
    {
        m_Properties.Closed = true;
    }

    WindowPrivate::WindowPrivate(
        std::unique_ptr<WindowClass> cls,
        std::unique_ptr<WindowProperties> properties,
        std::unique_ptr<WindowHandle> handle):
        m_Cls(std::move(cls)),
        m_Properties(std::move(properties)),
        m_Handle(std::move(handle))
    {
    }

    void *WindowPrivate::GetNativeHandle() const
    {
        return m_Handle->AsRawPtr();
    }

    const std::string &WindowPrivate::GetTitle() const
    {
        return m_Properties->Title;
    }

    const WindowSize &WindowPrivate::GetSize() const
    {
        return m_Properties->Size;
    }

    bool WindowPrivate::IsClosed() const
    {
        return m_Properties->Closed;
    }

    void WindowPrivate::Poll()
    {
        m_Handle->Poll();
    }

    std::unique_ptr<WindowPrivate> CreateWindowPrivate(const WindowSettings &settings)
    {
        auto cls = CreateNativeWindowClass("Eternal");
        auto properties = CreateWindowProperties(settings);
        auto listener = std::make_unique<WindowPropertyListener>(*properties);
        auto handle = cls->Instanciate(settings, std::move(listener));
        return std::make_unique<WindowPrivate>(std::move(cls), std::move(properties), std::move(handle));
    }

    WindowAdapter::WindowAdapter(WindowPrivate &window):
        m_Window(window)
    {
    }

    void *WindowAdapter::GetNativeHandle() const
    {
        return m_Window.GetNativeHandle();
    }

    const std::string &WindowAdapter::GetTitle() const
    {
        return m_Window.GetTitle();
    }

    const WindowSize &WindowAdapter::GetSize() const
    {
        return m_Window.GetSize();
    }
}
