#pragma once

#include <functional>
#include <memory>
#include <string_view>

#include <Windows.h>

#include <Eternal/Core/Window/WindowEvents.h>

namespace Eternal
{
    using WindowListener = std::function<void(WindowMessage)>;

    struct NativeWindowMessage
    {
        HWND Window;
        UINT Type;
        WPARAM Wparam;
        LPARAM Lparam;
    };

    LRESULT ProcessNativeWindowMessage(const WindowListener &listener, const NativeWindowMessage &message);

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
}
