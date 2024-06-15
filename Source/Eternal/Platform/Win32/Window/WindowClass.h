#pragma once

#include <functional>
#include <memory>
#include <string_view>

#include <Windows.h>

#include <Eternal/Core/Window/Window.h>

namespace Eternal
{
    using WindowListener = std::function<void(WindowEvent)>;

    class NativeWindow
    {
    private:
        struct Deleter
        {
            void operator()(HWND handle) const;
        };

        std::unique_ptr<HWND__, Deleter> m_Handle;
        std::unique_ptr<WindowListener> m_Listener;

    public:
        explicit NativeWindow(HWND handle, std::unique_ptr<WindowListener> listener);

        HWND GetHandle() const;
        void Show(int code);
        void SetTitle(std::string_view title);
        void SetPosition(Vector2 position);
        void Resize(Vector2 size);
    };

    class WindowClass
    {
    private:
        class Deleter
        {
        private:
            HINSTANCE m_Instance;

        public:
            explicit Deleter(HINSTANCE instance);

            void operator()(LPCWSTR className) const;
        };

        HINSTANCE m_Instance;
        std::unique_ptr<const wchar_t, Deleter> m_ClassName;

    public:
        explicit WindowClass(HINSTANCE instance, LPCWSTR className);

        NativeWindow Instanciate(const WindowSettings &settings, WindowListener listener);
    };

    WindowClass CreateWindowClass(HINSTANCE instance, std::string_view name);
}
