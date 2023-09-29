#include "Factory.h"

#include <Eternal/Platform/NativeWindow.h>

#include <Eternal/Private/Core/CorePlugin.h>

namespace Eternal
{
    std::unique_ptr<Application> CreateApplication(const std::string &name)
    {
        auto eventLoopProperties = std::make_unique<EventLoopProperties>();
        auto eventLoop = std::make_unique<EventLoop>(*eventLoopProperties);
        auto applicationLoop = std::make_unique<ApplicationLoop>(std::move(eventLoopProperties));

        auto logger = CreateConsoleLogger(name);

        auto windowClass = CreateNativeWindowClass("Eternal");
        auto windows = std::make_unique<WindowRegistry>(std::move(windowClass));
        auto windowManager = std::make_unique<WindowManager>(*windows);
        auto windowUpdater = std::make_unique<WindowUpdater>(std::move(windows));

        auto core = std::make_unique<CorePlugin>(*logger, *windowUpdater);

        auto engineProperties = std::make_unique<EngineProperties>();
        engineProperties->EventLoop = std::move(eventLoop);
        engineProperties->Logger = std::move(logger);
        engineProperties->WindowUpdater = std::move(windowUpdater);
        engineProperties->WindowManager = std::move(windowManager);

        auto engine = std::make_unique<Engine>(std::move(engineProperties));

        auto application = std::make_unique<Application>(std::move(applicationLoop), std::move(engine));

        application->AddPlugin(std::move(core));

        return application;
    }
}
