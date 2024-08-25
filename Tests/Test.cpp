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
    const auto &subtest = info.SubTest;
    const auto &source = info.Source;
    const auto *file = source.file_name();
    auto line = source.line();

    return std::format("Test case '{}.{}' failed {}:{}.", testCase, subtest, file, line);
}

void PrintFailureInfo(const FailureInfo &info)
{
    std::cout << FormatFailureInfo(info) << '\n';
}

TestCase::TestCase(std::string name, FailureHandler handler):
    m_Name(std::move(name)),
    m_Handler(std::move(handler))
{
}

int TestCase::Run(int argc, const char **argv)
{
    (void)argc;
    (void)argv;

    for (const auto &[name, test] : m_Tests)
    {
        try
        {
            test();
        }
        catch (const AssertionFailed &e)
        {
            m_Handler({
                .TestCase = m_Name,
                .SubTest = name,
                .Source = e.GetSource(),
            });

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
    return TestCase(std::move(name), [](const auto &info) { PrintFailureInfo(info); });
}

void Assert(bool value, std::source_location source)
{
    if (!value)
    {
        throw AssertionFailed(source);
    }
}
