#include "NativeWindow.h"

#include <memory>
#include <mutex>
#include <optional>

#include <Windows.h>

#include <Eternal/Core/Window/WindowEvents.h>

#include "GuiThread.h"
#include "NativeWindowHandle.h"
#include "Utils.h"
#include "WindowClass.h"

namespace
{
    using namespace Eternal;

    WindowHandle WrapWindowHandle(std::shared_ptr<NativeWindowHandle> nativeHandle, std::shared_ptr<EventBuffer> eventBuffer)
    {
        return {
            .NativePtr = nativeHandle->Get(),
            .Poll = [=] { return eventBuffer->Poll(); },
            .SetTitle = [=](auto title) { nativeHandle->SetTitle(title); },
            .SetPosition = [=](auto position) { nativeHandle->SetPosition(position); },
            .Resize = [=](auto size) { nativeHandle->Resize(size); },
        };
    }

    class NativeWindowFactory
    {
    private:
        GuiThread m_GuiThread;
        WindowClass m_WindowClass;

    public:
        explicit NativeWindowFactory(GuiThread guiThread, WindowClass windowClass):
            m_GuiThread(std::move(guiThread)),
            m_WindowClass(std::move(windowClass))
        {
        }

        WindowHandle CreateWindowHandle(const WindowSettings &settings)
        {
            auto events = std::make_shared<EventBuffer>();
            auto nativeHandle = CreateNativeWindowHandle(settings, *events);
            nativeHandle->Show(SW_NORMAL);
            return WrapWindowHandle(std::move(nativeHandle), std::move(events));
        }

    private:
        std::shared_ptr<NativeWindowHandle> CreateNativeWindowHandle(const WindowSettings &settings, EventBuffer &events)
        {
            auto handle = m_GuiThread.Run([&] { return m_WindowClass.Instanciate(settings, events); });
            return std::make_shared<NativeWindowHandle>(m_GuiThread, handle);
        }
    };
}

namespace Eternal
{
    WindowHandleFactory CreateNativeWindowHandleFactory()
    {
        auto guiThread = StartGuiThread();
        auto instance = GetModuleHandleW(nullptr);
        auto windowClass = CreateWindowClass(instance, "Eternal");
        auto factory = std::make_shared<NativeWindowFactory>(std::move(guiThread), std::move(windowClass));
        return [=](const auto &settings) { return factory->CreateWindowHandle(settings); };
    }
}
