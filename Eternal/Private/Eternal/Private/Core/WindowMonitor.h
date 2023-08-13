#pragma once

#include <memory>
#include <string>

#include <Eternal/Core/Window.h>

#include "WindowCommon.h"

namespace Eternal
{
    struct WindowProperties
    {
        std::string Title;
        WindowSize Size;
        bool Closed = false;
    };

    std::unique_ptr<WindowProperties> CreateWindowProperties(const WindowSettings &settings);

    class WindowPropertyListener : public WindowListener
    {
    private:
        WindowProperties &m_Properties;

    public:
        explicit WindowPropertyListener(WindowProperties &properties);

        virtual void OnSetTitle(const std::string &title) override;
        virtual void OnResize(const WindowSize &size) override;
        virtual void OnClose() override;
    };

    class WindowAdapter : public Window
    {
    private:
        WindowHandle &m_Handle;
        const WindowProperties &m_Properties;

    public:
        explicit WindowAdapter(WindowHandle &handle, const WindowProperties &properties);

        virtual void *GetNativeHandle() const override;
        virtual const std::string &GetTitle() const override;
        virtual const WindowSize &GetSize() const override;
        virtual bool IsClosed() const override;
    };

    class WindowMonitor
    {
    private:
        std::unique_ptr<WindowClass> m_Cls;
        std::unique_ptr<WindowProperties> m_Properties;
        std::unique_ptr<WindowHandle> m_Handle;
        std::unique_ptr<Window> m_Window;

    public:
        explicit WindowMonitor(
            std::unique_ptr<WindowClass> cls,
            std::unique_ptr<WindowProperties> properties,
            std::unique_ptr<WindowHandle> handle,
            std::unique_ptr<Window> window);

        Window &GetWindow() const;
        void Update();
    };

    std::unique_ptr<WindowMonitor> CreateWindowMonitor(const WindowSettings &settings);
}
