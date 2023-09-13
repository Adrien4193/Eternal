#pragma once

namespace Eternal
{
    struct EventLoopProperties
    {
        bool Running = false;
    };

    class EventLoop
    {
    private:
        EventLoopProperties &m_Properties;

    public:
        explicit EventLoop(EventLoopProperties &properties);

        void Stop();
    };
}
