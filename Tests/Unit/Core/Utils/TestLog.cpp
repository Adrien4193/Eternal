#include <Test.h>

#include <Eternal/Core/Logging/Logger.h>

using namespace Eternal;

int main(int argc, const char **argv)
{
    auto test = CreateTestCase("Log");

    test["LevelName"] = []
    {
        Assert(GetLogLevelName(LogLevel::Trace) == "Trace");
        Assert(GetLogLevelName(LogLevel::Debug) == "Debug");
        Assert(GetLogLevelName(LogLevel::Info) == "Info");
        Assert(GetLogLevelName(LogLevel::Warn) == "Warn");
        Assert(GetLogLevelName(LogLevel::Error) == "Error");
        Assert(GetLogLevelName(LogLevel::Fatal) == "Fatal");
    };

    test["FormatRecord"] = []
    {
        auto message = FormatLogRecord({
            .Name = "Test",
            .Level = LogLevel::Debug,
            .Message = "This is a test.",
        });

        Assert(message == "[Debug][Test]: This is a test.");
    };

    test["Logger"] = []
    {
        auto called = false;
        auto logger = Logger("Test", LogLevel::Debug, [&](auto &) { called = true; });

        Assert(logger.GetName() == "Test");

        Assert(logger.GetLevel() == LogLevel::Debug);

        Assert(logger.IsEnabled(LogLevel::Debug));
        Assert(!logger.IsEnabled(LogLevel::Trace));
        Assert(logger.IsEnabled(LogLevel::Info));

        logger.Trace("Not logged");
        Assert(!called);

        logger.Info("Logged");
        Assert(called);
    };

    return test.Run(argc, argv);
}
