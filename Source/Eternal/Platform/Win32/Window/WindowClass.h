#pragma once

#include <memory>
#include <string_view>

#include <Windows.h>

#include <Eternal/Core/Window/Window.h>

#include "NativeWindow.h"

namespace Eternal
{
    class WindowClass
    {
    private:
        struct Deleter
        {
            HINSTANCE Instance;

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
