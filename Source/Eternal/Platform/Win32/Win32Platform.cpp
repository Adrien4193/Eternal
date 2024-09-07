#include "Win32Platform.h"

#include <memory>

#include "Window/NativeWindowFactory.h"

namespace Eternal
{
    WindowManager CreateWindowManager()
    {
        auto instance = GetModuleHandleW(nullptr);
        auto factory = CreateNativeWindowFactory(instance);

        return WindowManager(std::move(factory));
    }
}
