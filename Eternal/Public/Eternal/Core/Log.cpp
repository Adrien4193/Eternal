#include "Log.h"

#include <iostream>
#include <stdexcept>

namespace Eternal
{
    auto GetLogLevelName(LogLevel level) -> std::string_view
    {
        switch (level)
        {
        case LogLevel::Trace:
            return "Trace";
        case LogLevel::Debug:
            return "Debug";
        case LogLevel::Info:
            return "Info";
        case LogLevel::Warn:
            return "Warn";
        case LogLevel::Error:
            return "Error";
        case LogLevel::Fatal:
            return "Fatal";
        case LogLevel::Off:
            return "Off";
        default:
            throw std::invalid_argument(std::to_string(static_cast<int>(level)));
        }
    }

    auto FormatLogRecord(const LogRecord &record) -> std::string
    {
        auto level = GetLogLevelName(record.Level);
        return std::format("[{}][{}]: {}", level, record.Name, record.Message);
    }

    void ConsoleLogHandler::Handle(const LogRecord &record)
    {
        std::cout << FormatLogRecord(record) << '\n';
    }

    Logger::Logger(std::string name, LogLevel level, std::unique_ptr<LogHandler> handler):
        m_Name(std::move(name)),
        m_Level(level),
        m_Handler(std::move(handler))
    {
    }

    auto Logger::GetName() const -> const std::string &
    {
        return m_Name;
    }

    auto Logger::GetLevel() const -> LogLevel
    {
        return m_Level;
    }

    void Logger::SetLevel(LogLevel level)
    {
        m_Level = level;
    }

    auto Logger::IsEnabled(LogLevel level) const -> bool
    {
        return level >= m_Level;
    }

    auto CreateConsoleLogger(std::string name) -> std::unique_ptr<Logger>
    {
        return std::make_unique<Logger>(std::move(name), LogLevel::Info, std::make_unique<ConsoleLogHandler>());
    }
}
