#pragma once

#include <memory>
#include <vector>

#include <Eternal/Core/Application.h>

#include "EngineMonitor.h"

namespace Eternal
{
    class ApplicationMonitor : public Application
    {
    private:
        std::unique_ptr<EngineMonitor> m_Monitor;
        std::vector<std::unique_ptr<Plugin>> m_Plugins;

    public:
        explicit ApplicationMonitor(std::unique_ptr<EngineMonitor> monitor, std::vector<std::unique_ptr<Plugin>> plugins);

        virtual Engine &GetEngine() const override;
        virtual void AddPlugin(std::unique_ptr<Plugin> plugin) override;
        virtual void Run() override;
    };
}
