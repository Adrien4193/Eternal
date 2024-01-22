#pragma once

#include <memory>

#include "EventLoop.h"
#include "Logger.h"

namespace Eternal
{
    class Engine
    {
    private:
        std::unique_ptr<EventLoop> m_EventLoop;
        std::unique_ptr<Logger> m_Logger;

    public:
        ETERNAL_EXPORT explicit Engine(std::unique_ptr<EventLoop> eventLoop, std::unique_ptr<Logger> logger);
        ~Engine() = default;

        Engine(const Engine &other) = delete;
        Engine &operator=(const Engine &other) = delete;
        Engine(Engine &&other) = delete;
        Engine &operator=(Engine &&other) = delete;

        ETERNAL_EXPORT EventLoop &GetEventLoop() const;
        ETERNAL_EXPORT Logger &GetLogger() const;
    };
}
