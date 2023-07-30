#pragma once

namespace Eternal
{
    class EventLoop
    {
    public:
        virtual ~EventLoop() = default;

        virtual void Stop() = 0;
    };
}
