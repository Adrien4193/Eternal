#pragma once

#include <memory>

#include <Windows.h>

#include <Eternal/Core/Window.h>

namespace Eternal
{
    class NativeWindowHandle : public WindowHandle
    {
    private:
        HWND m_Handle;
        std::unique_ptr<WindowListener> m_Listener;

    public:
        explicit NativeWindowHandle(HWND handle, std::unique_ptr<WindowListener> listener);
        ~NativeWindowHandle() override;

        void *AsRawPtr() const override;
        void Poll() override;
    };

    class NativeWindowClass : public WindowClass
    {
    private:
        HINSTANCE m_Instance;
        LPCWSTR m_ClassName;

    public:
        explicit NativeWindowClass(HINSTANCE instance, LPCWSTR className);
        ~NativeWindowClass() override;

        std::unique_ptr<WindowHandle> Instanciate(const WindowSettings &settings, std::unique_ptr<WindowListener> listener) override;
    };

    std::unique_ptr<WindowClass> CreateNativeWindowClass(HINSTANCE instance, const std::string &name);
    std::unique_ptr<WindowClass> CreateNativeWindowClass(const std::string &name);
}
