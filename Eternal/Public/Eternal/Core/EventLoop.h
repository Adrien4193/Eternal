#pragma once

#include <memory>

namespace Eternal
{
    struct EventLoopProperties
    {
        bool Running = false;
    };

    class ApplicationLoop
    {
    private:
        std::unique_ptr<EventLoopProperties> m_Properties;

    public:
        explicit ApplicationLoop(std::unique_ptr<EventLoopProperties> properties);

        bool IsRunning() const;
        void Start();
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
