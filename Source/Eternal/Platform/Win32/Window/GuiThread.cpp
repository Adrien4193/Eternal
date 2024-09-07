#include "GuiThread.h"

#include <cassert>
#include <memory>

#include <Eternal/Platform/Win32/Utils.h>

namespace
{
    using namespace Eternal;

    constexpr UINT GuiEventId = WM_USER;

    struct EventDeleter
    {
        void operator()(HANDLE handle) const
        {
            auto success = CloseHandle(handle);
            assert(success == TRUE);
        }
    };

    using EventPtr = std::unique_ptr<void, EventDeleter>;

    HANDLE CreateEventHandle()
    {
        auto *handle = CreateEventW(nullptr, FALSE, FALSE, nullptr);

        if (handle == nullptr)
        {
            throw LastErrorToException("Failed to create event");
        }

        return handle;
    }

    void Wait(HANDLE event)
    {
        auto code = WaitForSingleObjectEx(event, INFINITE, FALSE);

        if (code != WAIT_OBJECT_0)
        {
            throw LastErrorToException("Failed to wait for event");
        }
    }

    void Notify(HANDLE event)
    {
        auto success = SetEvent(event);

        if (success == FALSE)
        {
            throw LastErrorToException("Failed to set event");
        }
    }

    void ScheduleTask(DWORD threadId, const std::function<void()> &task)
    {
        auto wparam = reinterpret_cast<WPARAM>(&task);
        auto success = PostThreadMessageW(threadId, GuiEventId, wparam, 0);

        if (success == FALSE)
        {
            throw LastErrorToException("Failed to post message to GUI thread");
        }
    }

    void RunTask(WPARAM wparam)
    {
        const auto &task = *CastIntToPtr<const std::function<void()> *>(wparam);
        task();
    }

    void CreateMessageQueue()
    {
        auto message = MSG();
        PeekMessageW(&message, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    }

    void RunMessageLoop()
    {
        auto message = MSG();

        while (true)
        {
            auto code = GetMessageW(&message, nullptr, 0, 0);

            if (code <= 0)
            {
                return;
            }

            TranslateMessage(&message);

            if (message.hwnd != nullptr)
            {
                DispatchMessageW(&message);
                continue;
            }

            if (message.message == GuiEventId)
            {
                RunTask(message.wParam);
            }
        }
    }
}

namespace Eternal
{
    GuiThread::GuiThread(DWORD id, std::jthread thread):
        m_Id(id),
        m_Thread(std::move(thread))
    {
    }

    GuiThread::~GuiThread()
    {
        if (m_Thread.joinable())
        {
            auto success = PostThreadMessageW(m_Id, WM_QUIT, 0, 0);
            assert(success == TRUE);
        }
    }

    void GuiThread::Schedule(const std::function<void()> &task) const
    {
        ScheduleTask(m_Id, task);
    }

    GuiThread StartGuiThread()
    {
        auto *event = CreateEventHandle();
        auto holder = EventPtr(event);

        auto messageLoop = [=]
        {
            CreateMessageQueue();
            Notify(event);
            RunMessageLoop();
        };

        auto thread = std::jthread(messageLoop);

        Wait(event);

        auto *nativeThread = thread.native_handle();
        auto id = GetThreadId(nativeThread);

        return GuiThread(id, std::move(thread));
    }
}
