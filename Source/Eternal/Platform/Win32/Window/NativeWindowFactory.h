#pragma once

#include <Windows.h>

#include <Eternal/Core/Window/Window.h>

#include "GuiThread.h"
#include "WindowClass.h"

namespace Eternal
{
    class NativeWindowFactory
    {
    private:
        GuiThread m_GuiThread;
        WindowClass m_WindowClass;

    public:
        explicit NativeWindowFactory(GuiThread guiThread, WindowClass windowClass);

        WindowHandle CreateWindowHandle(const WindowSettings &settings);
    };

    WindowFactory CreateNativeWindowFactory(HINSTANCE instance);
}
