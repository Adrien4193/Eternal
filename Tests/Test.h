#pragma once

#include <concepts>
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
    std::string SubTest;
    std::source_location Source;
};

std::string FormatFailureInfo(const FailureInfo &info);

using FailureHandler = std::function<void(const FailureInfo &info)>;

void PrintFailureInfo(const FailureInfo &info);

class TestCase
{
private:
    std::string m_Name;
    FailureHandler m_Handler;
    std::unordered_map<std::string, std::function<void()>> m_Tests;

public:
    explicit TestCase(std::string name, FailureHandler handler);

    int Run(int argc, const char **argv);

    std::function<void()> &operator[](std::string name);
};

TestCase CreateTestCase(std::string name);

void Assert(bool value, std::source_location source = std::source_location::current());

template<typename ExceptionType, std::invocable<> CallableType>
void AssertThrow(CallableType &&callable, std::source_location source = std::source_location::current())
{
    try
    {
        std::forward<CallableType>(callable)();
    }
    catch (const ExceptionType &)
    {
        return;
    }

    throw AssertionFailed(source);
}
