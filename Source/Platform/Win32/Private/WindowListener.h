#pragma once

#include <memory>
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
        void Push(WindowEvent e)
        {
            auto lock = std::lock_guard(m_Mutex);
            m_Events.push_back(std::move(e));
        }

        std::vector<WindowEvent> Poll()
        {
            auto lock = std::lock_guard(m_Mutex);
            return std::exchange(m_Events, {});
        }
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
