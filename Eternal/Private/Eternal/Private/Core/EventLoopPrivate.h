#pragma once

#include <memory>

#include <Eternal/Core/EventLoop.h>

namespace Eternal
{
    class EventLoopPrivate
    {
    private:
        std::unique_ptr<EventLoopProperties> m_Properties;

    public:
        explicit EventLoopPrivate(std::unique_ptr<EventLoopProperties> properties);

        bool IsRunning() const;
        void Start();
    };
}
