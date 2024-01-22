#pragma once

#include <functional>

namespace Eternal
{
    class EventLoop
    {
    private:
        std::function<void()> m_Stop;

    public:
        ETERNAL_EXPORT explicit EventLoop(std::function<void()> stop);
        ~EventLoop() = default;

        EventLoop(const EventLoop &other) = delete;
        EventLoop &operator=(const EventLoop &other) = delete;
        EventLoop(EventLoop &&other) = delete;
        EventLoop &operator=(EventLoop &&other) = delete;

        ETERNAL_EXPORT void Stop();
    };
}
