#include "Factory.h"

#include <memory>

#include <Eternal/Core/Engine/Engine.h>

namespace
{
    using namespace Eternal;

    std::unique_ptr<EnginePrivate> CreateEnginePrivate(ApplicationSettings settings)
    {
        auto eventLoopPrivate = std::make_unique<EventLoopPrivate>();
        auto eventLoop = std::make_unique<EventLoop>(*eventLoopPrivate);

        auto logger = std::make_unique<Logger>(std::move(settings.Logger));

        auto windowManagerPrivate = std::make_unique<WindowManagerPrivate>(std::move(settings.WindowHandleFactory));
        auto windowManager = std::make_unique<WindowManager>(*windowManagerPrivate);

        auto enginePrivate = EnginePrivate{
            .EventLoopPrivate = std::move(eventLoopPrivate),
            .EventLoop = std::move(eventLoop),
            .Logger = std::move(logger),
            .WindowManagerPrivate = std::move(windowManagerPrivate),
            .WindowManager = std::move(windowManager),
        };

        return std::make_unique<EnginePrivate>(std::move(enginePrivate));
    }

    ApplicationScheduler CreateApplicationScheduler(EnginePrivate &engine)
    {
        auto scheduler = ApplicationScheduler();
        scheduler.OnStart([&] { engine.EventLoopPrivate->Running = true; });
        scheduler.OnUpdate([&] { engine.WindowManagerPrivate->PollWindows(); });
        return scheduler;
    }
}

namespace Eternal
{
    Application CreateApplication(ApplicationSettings settings)
    {
        auto enginePrivate = CreateEnginePrivate(std::move(settings));
        auto engine = std::make_unique<Engine>(*enginePrivate);
        auto scheduler = CreateApplicationScheduler(*enginePrivate);
        return Application(std::move(enginePrivate), std::move(engine), std::move(scheduler));
    }
}
