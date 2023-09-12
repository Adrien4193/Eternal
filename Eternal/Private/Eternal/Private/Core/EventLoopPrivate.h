#pragma once

#include <memory>

#include <Eternal/Core/EventLoop.h>

namespace Eternal
{
    class EventLoopPrivate
    {
    private:
        bool m_Running = false;

    public:
        bool IsRunning() const;
        void Start();
        void Stop();
    };

    class EventLoopAdapter : public EventLoop
    {
    private:
        EventLoopPrivate &m_EventLoop;

    public:
        explicit EventLoopAdapter(EventLoopPrivate &eventLoop);

        void Stop() override;
    };
}
