#include "Test.h"

#include <format>
#include <iostream>
#include <stdexcept>

AssertionFailed::AssertionFailed(std::source_location source):
    m_Source(source)
{
}

const std::source_location &AssertionFailed::GetSource() const
{
    return m_Source;
}

std::string FormatFailureInfo(const FailureInfo &info)
{
    const auto &testCase = info.TestCase;
    const auto &test = info.Test;
    const auto &source = info.Source;
    const auto *file = source.file_name();
    auto line = source.line();
    return std::format("Test case '{}.{}' failed at {}:{}.", testCase, test, file, line);
}

void ConsoleFailureHandler::Handle(const FailureInfo &info)
{
    auto message = FormatFailureInfo(info);
    std::cout << message << '\n';
}

TestCase::TestCase(std::string name, std::unique_ptr<FailureHandler> handler):
    m_Name(std::move(name)),
    m_Handler(std::move(handler))
{
}

int TestCase::Run()
{
    for (const auto &[name, test] : m_Tests)
    {
        try
        {
            test();
        }
        catch (const AssertionFailed &e)
        {
            auto info = FailureInfo();
            info.TestCase = m_Name;
            info.Test = name;
            info.Source = e.GetSource();
            m_Handler->Handle(info);
            return -1;
        }
    }
    return 0;
}

std::function<void()> &TestCase::operator[](std::string name)
{
    auto i = m_Tests.find(name);
    if (i != m_Tests.end())
    {
        auto message = std::format("Test '{}' declared twice", name);
        throw std::invalid_argument(message);
    }
    auto [j, inserted] = m_Tests.emplace(std::move(name), [] {});
    return j->second;
}

TestCase CreateTestCase(std::string name)
{
    return TestCase(std::move(name), std::make_unique<ConsoleFailureHandler>());
}

void Assert(bool value, std::source_location source)
{
    if (!value)
    {
        throw AssertionFailed(source);
    }
}

void AssertFalse(bool value, std::source_location source)
{
    Assert(!value, source);
}
