#include "WindowPrivate.h"

#include <Eternal/Platform/NativeWindow.h>

namespace Eternal
{
    auto CreateWindowProperties(const WindowSettings &settings) -> std::unique_ptr<WindowProperties>
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

    auto WindowPrivate::GetNativeHandle() const -> void *
    {
        return m_Handle->AsRawPtr();
    }

    auto WindowPrivate::GetTitle() const -> const std::string &
    {
        return m_Properties->Title;
    }

    auto WindowPrivate::GetSize() const -> const WindowSize &
    {
        return m_Properties->Size;
    }

    auto WindowPrivate::IsClosed() const -> bool
    {
        return m_Properties->Closed;
    }

    void WindowPrivate::Poll()
    {
        m_Handle->Poll();
    }

    auto CreateWindowPrivate(const WindowSettings &settings) -> std::unique_ptr<WindowPrivate>
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

    auto WindowAdapter::GetNativeHandle() const -> void *
    {
        return m_Window.GetNativeHandle();
    }

    auto WindowAdapter::GetTitle() const -> const std::string &
    {
        return m_Window.GetTitle();
    }

    auto WindowAdapter::GetSize() const -> const WindowSize &
    {
        return m_Window.GetSize();
    }
}
