#include "Factory.h"

#include <Eternal/Private/Core/ApplicationMonitor.h>
#include <Eternal/Private/Core/Core.h>
#include <Eternal/Private/Core/EngineMonitor.h>
#include <Eternal/Private/Core/EventLoopMonitor.h>
#include <Eternal/Private/Core/WindowMonitor.h>

namespace Eternal
{
    std::unique_ptr<Application> CreateApplication(const std::string &name)
    {
        auto eventLoopMonitor = CreateEventLoopMonitor();
        auto logger = CreateConsoleLogger(name);
        auto windowMonitor = CreateWindowMonitor({name, 200, 200});

        auto core = std::make_unique<Core>(*windowMonitor);

        auto properties = std::make_unique<EngineProperties>();
        properties->EventLoopMonitor = std::move(eventLoopMonitor);
        properties->Logger = std::move(logger);
        properties->WindowMonitor = std::move(windowMonitor);

        auto adapter = std::make_unique<EngineAdapter>(*properties);

        auto engine = std::make_unique<EngineMonitor>(std::move(properties), std::move(adapter));

        auto plugins = std::vector<std::unique_ptr<Plugin>>();
        plugins.push_back(std::move(core));

        return std::make_unique<ApplicationMonitor>(std::move(engine), std::move(plugins));
    }
}
