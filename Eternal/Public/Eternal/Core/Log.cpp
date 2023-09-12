#include "Log.h"

#include <iostream>
#include <stdexcept>

namespace Eternal
{
    std::string_view GetLogLevelName(LogLevel level)
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

    std::string FormatLogRecord(const LogRecord &record)
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

    const std::string &Logger::GetName() const
    {
        return m_Name;
    }

    LogLevel Logger::GetLevel() const
    {
        return m_Level;
    }

    void Logger::SetLevel(LogLevel level)
    {
        m_Level = level;
    }

    bool Logger::IsEnabled(LogLevel level) const
    {
        return level >= m_Level;
    }

    std::unique_ptr<Logger> CreateConsoleLogger(std::string name)
    {
        return std::make_unique<Logger>(std::move(name), LogLevel::Info, std::make_unique<ConsoleLogHandler>());
    }
}
