#pragma once

#include <memory>

#include <Eternal/Core/EventLoop.h>

namespace Eternal
{
    struct EventLoopProperties
    {
        bool Running = false;
    };

    class EventLoopAdapter : public EventLoop
    {
    private:
        EventLoopProperties &m_Properties;

    public:
        explicit EventLoopAdapter(EventLoopProperties &properties);

        virtual void Stop() override;
    };

    class EventLoopMonitor
    {
    private:
        std::unique_ptr<EventLoopProperties> m_Properties;
        std::unique_ptr<EventLoop> m_Loop;

    public:
        explicit EventLoopMonitor(std::unique_ptr<EventLoopProperties> properties, std::unique_ptr<EventLoop> loop);

        EventLoop &GetEventLoop() const;
        bool IsRunning() const;
        void Start();
    };

    std::unique_ptr<EventLoopMonitor> CreateEventLoopMonitor();
}
