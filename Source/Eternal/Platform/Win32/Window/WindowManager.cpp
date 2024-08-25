#include "WindowManager.h"

#include <memory>
#include <mutex>
#include <optional>
#include <utility>
#include <vector>

#include <Windows.h>

#include "GuiThread.h"
#include "Utils.h"
#include "WindowClass.h"

namespace
{
    using namespace Eternal;

    class MessageBuffer
    {
    private:
        std::mutex m_Mutex;
        std::vector<WindowMessage> m_Messages;

    public:
        void Add(WindowMessage message)
        {
            auto lock = std::lock_guard(m_Mutex);
            m_Messages.push_back(std::move(message));
        }

        std::vector<WindowMessage> Poll()
        {
            auto lock = std::lock_guard(m_Mutex);
            return std::exchange(m_Messages, {});
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

    class NativeWindowManager
    {
    private:
        GuiThread m_GuiThread;
        WindowClass m_WindowClass;

    public:
        explicit NativeWindowManager(GuiThread guiThread, WindowClass windowClass):
            m_GuiThread(std::move(guiThread)),
            m_WindowClass(std::move(windowClass))
        {
        }

        WindowHandle CreateWindowHandle(const WindowSettings &settings)
        {
            auto messages = std::make_shared<MessageBuffer>();
            auto listener = [=](WindowMessage message) { messages->Add(std::move(message)); };

            auto window = m_GuiThread.Run([&] { return m_WindowClass.Instanciate(settings, listener); });

            auto holder = std::make_shared<WindowHolder>(m_GuiThread, std::move(window));

            return WindowHandle{
                .NativePtr = holder->Get().GetHandle(),
                .Poll = [=] { return messages->Poll(); },
                .Show = [=] { holder->Get().Show(SW_NORMAL); },
                .SetTitle = [=](auto title) { holder->Get().SetTitle(title); },
                .SetPosition = [=](auto position) { holder->Get().SetPosition(position); },
                .Resize = [=](auto size) { holder->Get().Resize(size); },
            };
        }
    };
}

namespace Eternal
{
    WindowManager CreateNativeWindowManager()
    {
        auto guiThread = StartGuiThread();

        auto *instance = GetModuleHandleW(nullptr);

        auto windowClass = CreateWindowClass(instance, "Eternal");

        auto windowManager = std::make_shared<NativeWindowManager>(std::move(guiThread), std::move(windowClass));

        auto windowHandleFactory = [=](const auto &settings) { return windowManager->CreateWindowHandle(settings); };

        return WindowManager(std::move(windowHandleFactory));
    }
}
