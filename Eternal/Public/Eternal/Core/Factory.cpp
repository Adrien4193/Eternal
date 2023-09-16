#include "Factory.h"

#include <Eternal/Private/Core/EngineManager.h>
#include <Eternal/Private/Core/EventLoopManager.h>
#include <Eternal/Private/Core/WindowManager.h>

namespace Eternal
{
    std::unique_ptr<Application> CreateApplication(const std::string &name)
    {
        auto eventLoopManager = CreateEventLoopManager();

        auto logger = CreateConsoleLogger(name);

        auto windowSettings = WindowSettings();
        windowSettings.Title = name;
        windowSettings.Size = {400.0f, 400.0f};
        auto windowManager = CreateWindowManager(windowSettings);

        auto engine = std::make_unique<Engine>(eventLoopManager->GetEventLoop(), *logger, windowManager->GetWindow());

        auto engineManager = std::make_unique<EngineManager>(std::move(eventLoopManager), std::move(logger), std::move(windowManager));

        return std::make_unique<Application>(std::move(engine), std::move(engineManager));
    }
}
