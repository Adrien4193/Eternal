#include "Win32Platform.h"

#include <memory>

#include "Window/NativeWindowManager.h"

namespace Eternal
{
    WindowManager CreateWindowManager()
    {
        auto handle = GetModuleHandleW(nullptr);
        auto manager = CreateNativeWindowManager(handle);
        auto ptr = std::make_shared<decltype(manager)>(std::move(manager));
        auto factory = [=](const auto &settings) { return ptr->CreateWindowHandle(settings); };

        return WindowManager(std::move(factory));
    }
}
