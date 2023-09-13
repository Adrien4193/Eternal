#include "Factory.h"

#include <Eternal/Private/Core/EnginePrivate.h>
#include <Eternal/Private/Core/EventLoopPrivate.h>
#include <Eternal/Private/Core/WindowPrivate.h>

#include <Eternal/Platform/NativeWindow.h>

namespace
{
    using namespace Eternal;

    std::unique_ptr<WindowProperties> CreateWindowProperties(const WindowSettings &settings)
    {
        auto properties = std::make_unique<WindowProperties>();
        properties->Title = settings.Title;
        properties->Size = settings.Size;
        return properties;
    }
}

namespace Eternal
{
    std::unique_ptr<Application> CreateApplication(const std::string &name)
    {
        auto eventLoopProperties = std::make_unique<EventLoopProperties>();
        auto eventLoop = std::make_unique<EventLoop>(*eventLoopProperties);
        auto eventLoopPrivate = std::make_unique<EventLoopPrivate>(std::move(eventLoopProperties));

        auto logger = CreateConsoleLogger(name);

        auto windowClass = CreateNativeWindowClass("Eternal");
        auto windowSettings = WindowSettings{.Title = name, .Size = {400.0f, 400.0f}};
        auto windowProperties = CreateWindowProperties(windowSettings);
        auto windowListener = std::make_unique<WindowPropertyListener>(*windowProperties);
        auto windowHandle = windowClass->Instanciate(windowSettings, std::move(windowListener));
        auto window = std::make_unique<Window>(*windowHandle, *windowProperties);
        auto windowPrivate = std::make_unique<WindowPrivate>(std::move(windowHandle), std::move(windowProperties));

        auto engine = std::make_unique<Engine>(*eventLoop, *logger, *window);
        auto enginePrivate = std::make_unique<EnginePrivate>(
            std::move(eventLoop),
            std::move(eventLoopPrivate),
            std::move(logger),
            std::move(windowClass),
            std::move(window),
            std::move(windowPrivate));

        return std::make_unique<Application>(std::move(engine), std::move(enginePrivate));
    }
}
