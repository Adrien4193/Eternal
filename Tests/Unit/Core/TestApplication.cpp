#include <Test.h>

#include <Eternal/Core/Factory.h>

using namespace Eternal;

int main()
{
    auto test = CreateTestCase("Application");

    test["Run"] = []
    {
        auto settings = ApplicationSettings{
            .Logger = Logger("Test", LogLevel::Info, [&](auto &) {}),
            .WindowHandleFactory = [](const auto &) { return WindowHandle{}; },
        };

        auto application = CreateApplication(std::move(settings));
        auto &engine = application.GetEngine();
        auto &eventLoop = engine.GetEventLoop();

        auto started = false;
        auto stopped = false;
        auto updated = 0;

        auto update = [&]
        {
            if (++updated == 3)
            {
                eventLoop.Stop();
            }
        };

        application.OnStart([&] { started = true; });
        application.OnStop([&] { stopped = true; });
        application.OnUpdate(update);

        application.Run();

        Assert(started);
        Assert(stopped);
        Assert(updated == 3);
    };

    return test.Run();
}
