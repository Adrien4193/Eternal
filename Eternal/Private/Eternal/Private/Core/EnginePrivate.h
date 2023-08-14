#pragma once

#include <memory>

#include <Eternal/Core/Engine.h>
#include <Eternal/Core/Plugin.h>

#include "EventLoopPrivate.h"
#include "PluginManager.h"
#include "WindowPrivate.h"

namespace Eternal
{
    class EnginePrivate
    {
    private:
        std::unique_ptr<EventLoopPrivate> m_EventLoop;
        std::unique_ptr<Logger> m_Logger;
        std::unique_ptr<WindowPrivate> m_Window;
        PluginManager m_Plugins;

    public:
        explicit EnginePrivate(std::unique_ptr<EventLoopPrivate> eventLoop, std::unique_ptr<Logger> logger, std::unique_ptr<WindowPrivate> window);

        bool IsRunning() const;
        void AddPlugin(std::unique_ptr<Plugin> plugin);
        void Start();
        void Stop();
        void Update();
    };

    class EngineAdapter : public Engine
    {
    private:
        std::unique_ptr<EventLoop> m_EventLoop;
        Logger &m_Logger;
        std::unique_ptr<Window> m_Window;

    public:
        explicit EngineAdapter(std::unique_ptr<EventLoop> eventLoop, Logger &logger, std::unique_ptr<Window> window);

        virtual EventLoop &GetEventLoop() const override;
        virtual Logger &GetLogger() const override;
        virtual Window &GetWindow() const override;
    };
}
