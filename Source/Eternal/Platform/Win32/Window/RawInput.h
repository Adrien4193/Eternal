#pragma once

#include <Windows.h>

#include <Eternal/Core/Window/WindowEvents.h>

namespace Eternal
{
    WindowInput ParseRawInput(LPARAM lparam);
    void RegisterInputDevices(HWND window);
}
