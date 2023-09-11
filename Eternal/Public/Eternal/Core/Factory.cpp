#include "Factory.h"

#include <Eternal/Private/Core/ApplicationPrivate.h>
#include <Eternal/Private/Core/EnginePrivate.h>
#include <Eternal/Private/Core/EventLoopPrivate.h>
#include <Eternal/Private/Core/WindowPrivate.h>

namespace Eternal
{
    auto CreateApplication(const std::string &name) -> std::unique_ptr<Application>
    {
        auto eventLoop = std::make_unique<EventLoopPrivate>();
        auto eventLoopAdapter = std::make_unique<EventLoopAdapter>(*eventLoop);

        auto logger = CreateConsoleLogger(name);

        auto window = CreateWindowPrivate({name, 200, 200});
        auto windowAdapter = std::make_unique<WindowAdapter>(*window);

        auto engineAdapter = std::make_unique<EngineAdapter>(std::move(eventLoopAdapter), *logger, std::move(windowAdapter));
        auto engine = std::make_unique<EnginePrivate>(std::move(eventLoop), std::move(logger), std::move(window));

        return std::make_unique<ApplicationPrivate>(std::move(engine), std::move(engineAdapter));
    }
}
