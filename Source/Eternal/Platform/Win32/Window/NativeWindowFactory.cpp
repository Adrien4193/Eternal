#include "NativeWindowFactory.h"

#include <memory>
#include <mutex>
#include <optional>
#include <utility>
#include <vector>

#include <Eternal/Platform/Win32/Utils.h>

#include "RawInput.h"

namespace
{
    using namespace Eternal;

    class EventBuffer
    {
    private:
        std::mutex m_Mutex;
        std::vector<WindowEvent> m_Events;

    public:
        void Add(WindowEvent event)
        {
            auto lock = std::lock_guard(m_Mutex);
            m_Events.push_back(std::move(event));
        }

        std::vector<WindowEvent> Poll()
        {
            auto lock = std::lock_guard(m_Mutex);
            return std::exchange(m_Events, {});
        }
    };

    class WindowHolder
    {
    private:
        const GuiThread *m_GuiThread;
        std::optional<NativeWindow> m_Window;

    public:
        explicit WindowHolder(const GuiThread &guiThread, NativeWindow window):
            m_GuiThread(&guiThread),
            m_Window(std::move(window))
        {
        }

        ~WindowHolder()
        {
            m_GuiThread->Run([&] { m_Window.reset(); });
        }

        WindowHolder(const WindowHolder &) = delete;
        WindowHolder(WindowHolder &&) = delete;
        WindowHolder &operator=(const WindowHolder &) = delete;
        WindowHolder &operator=(WindowHolder &&) = delete;

        NativeWindow &Get()
        {
            return *m_Window;
        }
    };
}

namespace Eternal
{
    NativeWindowFactory::NativeWindowFactory(GuiThread guiThread, WindowClass windowClass):
        m_GuiThread(std::move(guiThread)),
        m_WindowClass(std::move(windowClass))
    {
    }

    WindowHandle NativeWindowFactory::CreateWindowHandle(const WindowSettings &settings)
    {
        auto events = std::make_shared<EventBuffer>();
        auto listener = [=](auto event) { events->Add(std::move(event)); };

        auto window = m_GuiThread.Run([&] { return m_WindowClass.Instanciate(settings, listener); });

        RegisterInputDevices(window.GetHandle());

        auto holder = std::make_shared<WindowHolder>(m_GuiThread, std::move(window));

        return WindowHandle{
            .NativePtr = holder->Get().GetHandle(),
            .Poll = [=] { return events->Poll(); },
            .Show = [=] { holder->Get().Show(SW_NORMAL); },
            .SetTitle = [=](auto title) { holder->Get().SetTitle(title); },
            .SetPosition = [=](auto position) { holder->Get().SetPosition(position); },
            .Resize = [=](auto size) { holder->Get().Resize(size); },
        };
    }

    WindowFactory CreateNativeWindowFactory(HINSTANCE instance)
    {
        auto guiThread = StartGuiThread();
        auto windowClass = CreateWindowClass(instance, "Eternal");

        auto manager = std::make_shared<NativeWindowFactory>(std::move(guiThread), std::move(windowClass));

        return [=](const auto &settings) { return manager->CreateWindowHandle(settings); };
    }
}
