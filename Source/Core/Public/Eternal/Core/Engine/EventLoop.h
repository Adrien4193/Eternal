#pragma once

namespace Eternal
{
    struct EventLoopPrivate
    {
        bool Running = false;
    };

    class EventLoop
    {
    private:
        EventLoopPrivate &m_EventLoop;

    public:
        ETERNAL_CORE_API explicit EventLoop(EventLoopPrivate &eventLoop);
        ~EventLoop() = default;

        EventLoop(const EventLoop &other) = delete;
        EventLoop &operator=(const EventLoop &other) = delete;
        EventLoop(EventLoop &&other) = delete;
        EventLoop &operator=(EventLoop &&other) = delete;

        ETERNAL_CORE_API void Stop();
    };
}
