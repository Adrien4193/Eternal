#pragma once

#include <functional>
#include <memory>
#include <string_view>

#include <Windows.h>

#include <Eternal/Core/Window/WindowEvents.h>
#include <Eternal/Core/Window/WindowSettings.h>

#include "WindowListener.h"

namespace Eternal
{
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

        HWND Instanciate(const WindowSettings &settings, EventBuffer &events);
    };

    WindowClass CreateWindowClass(HINSTANCE instance, std::string_view name);
}
