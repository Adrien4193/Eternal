#include <Test.h>

#include <Eternal/Core/Application.h>

using namespace Eternal;

int main(int argc, const char **argv)
{
    auto test = CreateTestCase("Application");

    test["Run"] = []
    {
        auto started = false;
        auto stopped = false;
        auto updated = 0;

        auto application = Application({
            .IsRunning = [&] { return updated < 3; },
            .Start = [&] { started = true; },
            .Stop = [&] { stopped = true; },
            .Update = [&] { ++updated; },
        });

        application.Run();

        Assert(started);
        Assert(stopped);
        Assert(updated == 3);
    };

    return test.Run(argc, argv);
}
