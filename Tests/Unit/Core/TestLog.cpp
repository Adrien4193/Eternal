#include <Test.h>

#include <Eternal/Utils/Log.h>

class MockHandler : public Eternal::LogHandler
{
private:
    bool &m_Called;

public:
    explicit MockHandler(bool &called):
        m_Called(called)
    {
    }

    virtual void Handle(const Eternal::LogRecord &record) override
    {
        (void)record;
        m_Called = true;
    }
};

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
        auto expected = "[Debug][Test]: This is a test.";
        Assert(message == expected);
    };

    test["Logger"] = []
    {
        auto called = false;
        auto logger = Eternal::Logger("Test", Eternal::LogLevel::Debug, std::make_unique<MockHandler>(called));

        Assert(logger.GetName() == "Test");

        Assert(logger.GetLevel() == Eternal::LogLevel::Debug);

        Assert(logger.IsEnabled(Eternal::LogLevel::Debug));
        Assert(!logger.IsEnabled(Eternal::LogLevel::Trace));
        Assert(logger.IsEnabled(Eternal::LogLevel::Info));

        logger.Trace("Not logged");
        Assert(!called);

        logger.Info("Not logged");
        Assert(called);
    };

    return test.Run();
}
