#pragma once

#include <memory>

#include <Eternal/Core/Logging/Logger.h>
#include <Eternal/Core/Window/WindowManager.h>

#include "EventLoop.h"

namespace Eternal
{
    struct EnginePrivate
    {
        std::unique_ptr<EventLoopPrivate> EventLoopPrivate;
        std::unique_ptr<EventLoop> EventLoop;
        std::unique_ptr<Logger> Logger;
        std::unique_ptr<WindowManagerPrivate> WindowManagerPrivate;
        std::unique_ptr<WindowManager> WindowManager;
    };

    class Engine
    {
    private:
        EnginePrivate &m_Engine;

    public:
        ETERNAL_CORE_API explicit Engine(EnginePrivate &engine);

        Engine(const Engine &other) = delete;
        Engine &operator=(const Engine &other) = delete;
        Engine(Engine &&other) = delete;
        Engine &operator=(Engine &&other) = delete;

        ETERNAL_CORE_API EventLoop &GetEventLoop() const;
        ETERNAL_CORE_API Logger &GetLogger() const;
        ETERNAL_CORE_API WindowManager &GetWindowManager() const;
    };
}
