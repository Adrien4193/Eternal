#pragma once

#include <exception>
#include <functional>
#include <memory>
#include <source_location>
#include <string>
#include <unordered_map>

class AssertionFailed
{
private:
    std::source_location m_Source;

public:
    explicit AssertionFailed(std::source_location source);

    const std::source_location &GetSource() const;
};

struct FailureInfo
{
    std::string TestCase;
    std::string Test;
    std::source_location Source;
};

std::string FormatFailureInfo(const FailureInfo &info);

class FailureHandler
{
public:
    virtual ~FailureHandler() = default;

    virtual void Handle(const FailureInfo &info) = 0;
};

class ConsoleFailureHandler : public FailureHandler
{
public:
    void Handle(const FailureInfo &info) override;
};

class TestCase
{
private:
    std::string m_Name;
    std::unique_ptr<FailureHandler> m_Handler;
    std::unordered_map<std::string, std::function<void()>> m_Tests;

public:
    explicit TestCase(std::string name, std::unique_ptr<FailureHandler> handler);

    int Run();

    std::function<void()> &operator[](std::string name);
};

TestCase CreateTestCase(std::string name);

void Assert(bool value, std::source_location source = std::source_location::current());
void AssertFalse(bool value, std::source_location source = std::source_location::current());

template<typename ExceptionType, typename CallableType>
void AssertThrow(CallableType &&callable, std::source_location source = std::source_location::current())
{
    try
    {
        callable();
    }
    catch (const ExceptionType &)
    {
        return;
    }
    throw AssertionFailed(source);
}
