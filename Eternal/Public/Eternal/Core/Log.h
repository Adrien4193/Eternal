#pragma once

#include <format>
#include <memory>
#include <string>
#include <string_view>

namespace Eternal
{
    enum class LogLevel
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Fatal,
        Off,
    };

    std::string_view GetLogLevelName(LogLevel level);

    struct LogRecord
    {
        std::string_view Name;
        LogLevel Level = LogLevel::Info;
        std::string_view Message;
    };

    std::string FormatLogRecord(const LogRecord &record);

    class LogHandler
    {
    public:
        virtual ~LogHandler() = default;

        virtual void Handle(const LogRecord &record) = 0;
    };

    class ConsoleLogHandler : public LogHandler
    {
    public:
        virtual void Handle(const LogRecord &record) override;
    };

    class Logger
    {
    private:
        std::string m_Name;
        LogLevel m_Level;
        std::unique_ptr<LogHandler> m_Handler;

    public:
        explicit Logger(std::string name, LogLevel level, std::unique_ptr<LogHandler> handler);

        const std::string &GetName() const;
        LogLevel GetLevel() const;
        void SetLevel(LogLevel level);
        bool IsEnabled(LogLevel level) const;

        template<typename... Args>
        void Log(LogLevel level, std::format_string<Args...> format, Args &&...args)
        {
            if (!IsEnabled(level))
            {
                return;
            }
            auto message = std::format(format, std::forward<Args>(args)...);
            auto record = LogRecord(m_Name, m_Level, message);
            m_Handler->Handle(record);
        }

        template<typename... Args>
        void Trace(std::format_string<Args...> format, Args &&...args)
        {
            Log(LogLevel::Trace, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Debug(std::format_string<Args...> format, Args &&...args)
        {
            Log(LogLevel::Debug, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Info(std::format_string<Args...> format, Args &&...args)
        {
            Log(LogLevel::Info, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Warn(std::format_string<Args...> format, Args &&...args)
        {
            Log(LogLevel::Warn, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Error(std::format_string<Args...> format, Args &&...args)
        {
            Log(LogLevel::Error, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void Fatal(std::format_string<Args...> format, Args &&...args)
        {
            Log(LogLevel::Fatal, format, std::forward<Args>(args)...);
        }
    };

    std::unique_ptr<Logger> CreateConsoleLogger(std::string name);
}
