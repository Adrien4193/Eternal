#include <Test.h>

#include <Eternal/Core/Application.h>

Eternal::Engine MockEngine(Eternal::EventLoopProperties &properties)
{
    auto eventLoop = Eternal::EventLoop(properties);
    auto logger = Eternal::Logger("Test", Eternal::LogLevel::Info, [](auto &) {});
    return Eternal::Engine(std::move(eventLoop), std::move(logger));
}

int main()
{
    auto test = CreateTestCase("Application");

    test["Run"] = []
    {
        auto properties = Eternal::EventLoopProperties();
        properties.Running = true;

        auto loop = Eternal::ApplicationLoop(properties);

        auto engine = MockEngine(properties);
        auto application = Eternal::Application(std::move(engine), std::move(loop));

        auto started = false;
        auto stopped = false;
        auto updated = 0;

        auto update = [&]
        {
            if (++updated == 3)
            {
                properties.Running = false;
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
