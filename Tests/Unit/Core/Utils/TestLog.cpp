#include <Test.h>

#include <Eternal/Core/Utils/Log.h>

int main()
{
    auto test = CreateTestCase("Log");

    test["LevelName"] = []
    {
        Assert(Eternal::GetLogLevelName(Eternal::LogLevel::Trace) == "Trace");
        Assert(Eternal::GetLogLevelName(Eternal::LogLevel::Debug) == "Debug");
        Assert(Eternal::GetLogLevelName(Eternal::LogLevel::Info) == "Info");
        Assert(Eternal::GetLogLevelName(Eternal::LogLevel::Warn) == "Warn");
        Assert(Eternal::GetLogLevelName(Eternal::LogLevel::Error) == "Error");
        Assert(Eternal::GetLogLevelName(Eternal::LogLevel::Fatal) == "Fatal");
    };

    test["FormatRecord"] = []
    {
        auto record = Eternal::LogRecord();
        record.Name = "Test";
        record.Level = Eternal::LogLevel::Debug;
        record.Message = "This is a test.";

        auto message = Eternal::FormatLogRecord(record);
        const auto *expected = "[Debug][Test]: This is a test.";
        Assert(message == expected);
    };

    test["Logger"] = []
    {
        auto called = false;
        auto logger = Eternal::Logger("Test", Eternal::LogLevel::Debug, [&](auto &) { called = true; });

        Assert(logger.GetName() == "Test");

        Assert(logger.GetLevel() == Eternal::LogLevel::Debug);

        Assert(logger.IsEnabled(Eternal::LogLevel::Debug));
        Assert(!logger.IsEnabled(Eternal::LogLevel::Trace));
        Assert(logger.IsEnabled(Eternal::LogLevel::Info));

        logger.Trace("Not logged");
        Assert(!called);

        logger.Info("Logged");
        Assert(called);
    };

    return test.Run();
}
