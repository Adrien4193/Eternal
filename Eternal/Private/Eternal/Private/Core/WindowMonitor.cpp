#include "WindowMonitor.h"

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

    WindowAdapter::WindowAdapter(WindowHandle &handle, const WindowProperties &properties):
        m_Handle(handle),
        m_Properties(properties)
    {
    }

    void *WindowAdapter::GetNativeHandle() const
    {
        return m_Handle.AsRawPtr();
    }

    const std::string &WindowAdapter::GetTitle() const
    {
        return m_Properties.Title;
    }

    const WindowSize &WindowAdapter::GetSize() const
    {
        return m_Properties.Size;
    }

    bool WindowAdapter::IsClosed() const
    {
        return m_Properties.Closed;
    }

    WindowMonitor::WindowMonitor(
        std::unique_ptr<WindowClass> cls,
        std::unique_ptr<WindowProperties> properties,
        std::unique_ptr<WindowHandle> handle,
        std::unique_ptr<Window> window):
        m_Cls(std::move(cls)),
        m_Properties(std::move(properties)),
        m_Handle(std::move(handle)),
        m_Window(std::move(window))
    {
    }

    Window &WindowMonitor::GetWindow() const
    {
        return *m_Window;
    }

    void WindowMonitor::ShowWindow()
    {
        m_Handle->Show();
    }

    void WindowMonitor::Update()
    {
        m_Handle->Poll();
    }

    std::unique_ptr<WindowMonitor> CreateWindowMonitor(const WindowSettings &settings)
    {
        auto cls = CreateWindowClass("Eternal");
        auto properties = CreateWindowProperties(settings);
        auto listener = std::make_unique<WindowPropertyListener>(*properties);
        auto handle = cls->Instanciate(settings, std::move(listener));
        auto adapter = std::make_unique<WindowAdapter>(*handle, *properties);
        return std::make_unique<WindowMonitor>(std::move(cls), std::move(properties), std::move(handle), std::move(adapter));
    }
}
