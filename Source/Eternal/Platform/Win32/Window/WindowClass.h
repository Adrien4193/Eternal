#pragma once

#include <memory>
#include <string_view>

#include <Windows.h>

#include <Eternal/Core/Window/WindowSettings.h>

#include "GuiThread.h"
#include "WindowHandle.h"

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

        GuiThread m_GuiThread;
        HINSTANCE m_Instance;
        std::unique_ptr<const wchar_t, Deleter> m_ClassName;

    public:
        explicit WindowClass(GuiThread guiThread, HINSTANCE instance, LPCWSTR className);

        NativeWindowHandle Instanciate(const WindowSettings &settings);
    };

    WindowClass CreateWindowClass(GuiThread guiThread, HINSTANCE instance, std::string_view name);
}
