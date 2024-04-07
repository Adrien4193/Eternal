#include <Test.h>

#include <Eternal/Core/Application.h>

using namespace Eternal;

int main()
{
    auto test = CreateTestCase("Application");

    test["Run"] = []
    {
        auto application = Application();

        auto started = false;
        auto stopped = false;
        auto updated = 0;

        auto update = [&]
        {
            if (++updated == 3)
            {
                application.Quit();
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
