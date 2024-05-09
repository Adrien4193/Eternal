#include "WindowHandleFactory.h"

#include <memory>

#include <Windows.h>

#include "GuiThread.h"
#include "Utils.h"
#include "WindowClass.h"
#include "WindowHandle.h"

namespace Eternal
{
    WindowHandleFactory CreateNativeWindowHandleFactory()
    {
        auto guiThread = StartGuiThread();

        auto *instance = GetModuleHandleW(nullptr);

        auto windowClass = CreateWindowClass(std::move(guiThread), instance, "Eternal");

        auto windowClassPtr = std::make_shared<WindowClass>(std::move(windowClass));

        return [=](const auto &settings)
        {
            auto handle = windowClassPtr->Instanciate(settings);

            auto handlePtr = std::make_shared<NativeWindowHandle>(std::move(handle));

            return WindowHandle{
                .NativePtr = handlePtr->Get(),
                .Poll = [=] { return handlePtr->Poll(); },
                .Show = [=] { handlePtr->Show(SW_NORMAL); },
                .SetTitle = [=](auto title) { handlePtr->SetTitle(title); },
                .SetPosition = [=](auto position) { handlePtr->SetPosition(position); },
                .Resize = [=](auto size) { handlePtr->Resize(size); },
            };
        };
    }
}
