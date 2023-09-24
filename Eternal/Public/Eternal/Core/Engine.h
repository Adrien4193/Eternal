#pragma once

#include <memory>

#include <Eternal/Core/Log.h>

#include "EventLoop.h"
#include "Window.h"

namespace Eternal
{
    struct EngineProperties
    {
        std::unique_ptr<EventLoop> EventLoop;
        std::unique_ptr<Logger> Logger;
        std::unique_ptr<WindowManager> WindowManager;
    };

    class Engine
    {
    private:
        std::unique_ptr<EngineProperties> m_Properties;

    public:
        explicit Engine(std::unique_ptr<EngineProperties> properties);

        EventLoop &GetEventLoop() const;
        Logger &GetLogger() const;
        WindowManager &GetWindowManager() const;
    };
}
