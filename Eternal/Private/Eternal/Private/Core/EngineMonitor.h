#pragma once

#include <memory>

#include <Eternal/Core/Engine.h>
#include <Eternal/Utils/Log.h>

#include "EventLoopMonitor.h"
#include "WindowMonitor.h"

namespace Eternal
{
    struct EngineProperties
    {
        std::unique_ptr<EventLoopMonitor> EventLoopMonitor;
        std::unique_ptr<Logger> Logger;
        std::unique_ptr<WindowMonitor> WindowMonitor;
    };

    class EngineAdapter : public Engine
    {
    private:
        EngineProperties &m_Properties;

    public:
        explicit EngineAdapter(EngineProperties &properties);

        virtual EventLoop &GetEventLoop() const override;
        virtual Logger &GetLogger() const override;
        virtual Window &GetWindow() const override;
    };

    class EngineMonitor
    {
    private:
        std::unique_ptr<EngineProperties> m_Properties;
        std::unique_ptr<Engine> m_Engine;

    public:
        explicit EngineMonitor(std::unique_ptr<EngineProperties> properties, std::unique_ptr<Engine> engine);

        Engine &GetEngine() const;
        bool IsRunning() const;
        void Start();
    };
}
