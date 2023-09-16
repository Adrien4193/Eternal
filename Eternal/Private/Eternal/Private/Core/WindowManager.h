#pragma once

#include <memory>
#include <string>

#include <Eternal/Core/Window.h>

#include "WindowClass.h"

namespace Eternal
{
    class WindowPropertyListener : public WindowListener
    {
    private:
        WindowProperties &m_Properties;

    public:
        explicit WindowPropertyListener(WindowProperties &properties);

        void SetTitle(const std::string &title) override;
        void Resize(const Vector2 &size) override;
        void Close() override;
    };

    struct WindowHolder
    {
        std::unique_ptr<WindowProperties> Properties;
        std::unique_ptr<WindowHandle> Handle;
        std::unique_ptr<Window> Window;
    };

    class WindowManager
    {
    private:
        std::unique_ptr<WindowClass> m_Cls;
        WindowHolder m_Window;

    public:
        explicit WindowManager(std::unique_ptr<WindowClass> cls, WindowHolder window);

        Window &GetWindow() const;
        bool IsClosed() const;
        void Update();
    };

    std::unique_ptr<WindowManager> CreateWindowManager(const WindowSettings &settings);
}
