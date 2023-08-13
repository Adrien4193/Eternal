#pragma once

#include <memory>

#include <Windows.h>

#include <Eternal/Private/Core/WindowCommon.h>

namespace Eternal
{
    class NativeWindowHandle : public WindowHandle
    {
    private:
        HWND m_Handle;
        std::unique_ptr<WindowListener> m_Listener;

    public:
        explicit NativeWindowHandle(HWND handle, std::unique_ptr<WindowListener> listener);
        virtual ~NativeWindowHandle();

        virtual void *AsRawPtr() const override;
        virtual void Poll() override;
        virtual void Show() override;
    };

    class NativeWindowClass : public WindowClass
    {
    private:
        HINSTANCE m_Instance;
        LPCWSTR m_ClassName;

    public:
        explicit NativeWindowClass(HINSTANCE instance, LPCWSTR className);
        ~NativeWindowClass();

        virtual std::unique_ptr<WindowHandle> Instanciate(const WindowSettings &settings, std::unique_ptr<WindowListener> listener) override;
    };

    std::unique_ptr<WindowClass> CreateWindowClass(HINSTANCE instance, const std::string &name);
    std::unique_ptr<WindowClass> CreateWindowClass(const std::string &name);
}
