#include "WindowHandleFactory.h"

#include <memory>

#include <Windows.h>

#include "GuiThread.h"
#include "NativeWindowHandle.h"
#include "NativeWindowManager.h"
#include "Utils.h"

namespace Eternal
{
    WindowHandleFactory CreateNativeWindowHandleFactory()
    {
        auto guiThread = StartGuiThread();

        auto *instance = GetModuleHandleW(nullptr);

        auto windowClass = CreateWindowClass(instance, "Eternal");

        auto windowManager = std::make_shared<NativeWindowManager>(std::move(guiThread), std::move(windowClass));

        return [=](const auto &settings)
        {
            auto handle = windowManager->CreateWindowHandle(settings);

            auto ptr = std::make_shared<NativeWindowHandle>(std::move(handle));

            return WindowHandle{
                .NativePtr = ptr->Get(),
                .Poll = [=] { return ptr->Poll(); },
                .Show = [=] { ptr->Show(SW_NORMAL); },
                .SetTitle = [=](auto title) { ptr->SetTitle(title); },
                .SetPosition = [=](auto position) { ptr->SetPosition(position); },
                .Resize = [=](auto size) { ptr->Resize(size); },
            };
        };
    }
}
