#pragma once

#include <memory>

#include <Eternal/Core/EventLoop.h>

namespace Eternal
{
    class EventLoopManager
    {
    private:
        std::unique_ptr<EventLoopProperties> m_Properties;
        std::unique_ptr<EventLoop> m_EventLoop;

    public:
        explicit EventLoopManager(std::unique_ptr<EventLoopProperties> properties, std::unique_ptr<EventLoop> eventLoop);

        EventLoop &GetEventLoop() const;
        bool IsRunning() const;
        void Start();
        void Stop();
    };

    std::unique_ptr<EventLoopManager> CreateEventLoopManager();
}
