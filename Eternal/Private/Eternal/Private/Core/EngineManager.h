#pragma once

#include <memory>

#include <Eternal/Core/Log.h>

#include "EventLoopManager.h"
#include "PluginManager.h"
#include "WindowManager.h"

namespace Eternal
{
    class EngineManager
    {
    private:
        std::unique_ptr<EventLoopManager> m_EventLoopManager;
        std::unique_ptr<Logger> m_Logger;
        std::unique_ptr<WindowManager> m_WindowManager;
        PluginManager m_Plugins;

    public:
        explicit EngineManager(
            std::unique_ptr<EventLoopManager> eventLoopManager,
            std::unique_ptr<Logger> logger,
            std::unique_ptr<WindowManager> windowManager);

        void AddPlugin(std::unique_ptr<Plugin> plugin);
        void Run();

    private:
        void Start();
        void Stop();
        void Update();
    };
}
