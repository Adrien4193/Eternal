#pragma once

#include <mutex>
#include <vector>

#include <Windows.h>

#include <Eternal/Core/Window/WindowEvents.h>

namespace Eternal
{
    class EventBuffer
    {
    private:
        std::mutex m_Mutex;
        std::vector<WindowEvent> m_Events;

    public:
        void Push(WindowEvent e);
        std::vector<WindowEvent> Poll();
    };

    struct WindowMessage
    {
        HWND Window;
        UINT Type;
        WPARAM Wparam;
        LPARAM Lparam;
    };

    LRESULT ProcessWindowMessage(const WindowMessage &message, EventBuffer &events);
}
