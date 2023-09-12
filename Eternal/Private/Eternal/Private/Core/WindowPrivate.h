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

        void OnSetTitle(const std::string &title) override;
        void OnResize(const WindowSize &size) override;
        void OnClose() override;
    };

    class WindowPrivate
    {
    private:
        std::unique_ptr<WindowClass> m_Cls;
        std::unique_ptr<WindowProperties> m_Properties;
        std::unique_ptr<WindowHandle> m_Handle;

    public:
        explicit WindowPrivate(std::unique_ptr<WindowClass> cls, std::unique_ptr<WindowProperties> properties, std::unique_ptr<WindowHandle> handle);

        void *GetNativeHandle() const;
        const std::string &GetTitle() const;
        const WindowSize &GetSize() const;
        bool IsClosed() const;
        void Poll();
    };

    std::unique_ptr<WindowPrivate> CreateWindowPrivate(const WindowSettings &settings);

    class WindowAdapter : public Window
    {
    private:
        WindowPrivate &m_Window;

    public:
        explicit WindowAdapter(WindowPrivate &window);

        void *GetNativeHandle() const override;
        const std::string &GetTitle() const override;
        const WindowSize &GetSize() const override;
    };
}
