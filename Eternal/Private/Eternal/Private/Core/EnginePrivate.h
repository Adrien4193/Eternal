#pragma once

#include <memory>

#include <Eternal/Core/Log.h>
#include <Eternal/Core/Plugin.h>

#include "EventLoopPrivate.h"
#include "PluginManager.h"
#include "WindowPrivate.h"

namespace Eternal
{
    class EnginePrivate
    {
    private:
        std::unique_ptr<EventLoop> m_EventLoop;
        std::unique_ptr<EventLoopPrivate> m_EventLoopPrivate;
        std::unique_ptr<Logger> m_Logger;
        std::unique_ptr<WindowClass> m_WindowClass;
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<WindowPrivate> m_WindowPrivate;
        PluginManager m_Plugins;

    public:
        explicit EnginePrivate(
            std::unique_ptr<EventLoop> eventLoop,
            std::unique_ptr<EventLoopPrivate> eventLoopPrivate,
            std::unique_ptr<Logger> logger,
            std::unique_ptr<WindowClass> windowClass,
            std::unique_ptr<Window> window,
            std::unique_ptr<WindowPrivate> windowPrivate);

        void AddPlugin(std::unique_ptr<Plugin> plugin);
        void Run();

    private:
        void Start();
        void Stop();
        void Update();
    };
}
