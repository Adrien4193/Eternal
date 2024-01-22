#include "Factory.h"

#include <memory>

#include "EnginePrivate.h"

namespace Eternal
{
    Application CreateApplication(const ApplicationSettings &settings)
    {
        auto enginePrivate = std::make_shared<EnginePrivate>();

        auto eventLoop = EventLoop(enginePrivate->EventLoop);

        auto logger = CreateConsoleLogger("Eternal");

        auto engine = Engine(std::move(eventLoop), std::move(logger));

        auto applicationLoop = ApplicationLoop(enginePrivate->EventLoop);
        auto application = Application(std::move(engine), std::move(applicationLoop));

        application.OnStart([=] { enginePrivate->EventLoop.Running = true; });

        return application;
    }
}
