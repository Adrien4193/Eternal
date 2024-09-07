#pragma once

#include <Windows.h>

#include <Eternal/Core/Window/Window.h>

#include "GuiThread.h"
#include "WindowClass.h"

namespace Eternal
{
    class NativeWindowManager
    {
    private:
        GuiThread m_GuiThread;
        WindowClass m_WindowClass;

    public:
        explicit NativeWindowManager(GuiThread guiThread, WindowClass windowClass);

        WindowHandle CreateWindowHandle(const WindowSettings &settings);
    };

    NativeWindowManager CreateNativeWindowManager(HINSTANCE instance);
}
