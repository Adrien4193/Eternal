#pragma once

#include <format>
#include <functional>
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

    ETERNAL_CORE_API std::string_view GetLogLevelName(LogLevel level);

    struct LogRecord
    {
        std::string_view Name;
        LogLevel Level = LogLevel::Info;
        std::string_view Message;
    };

    ETERNAL_CORE_API std::string FormatLogRecord(const LogRecord &record);

    using LogHandler = std::function<void(const LogRecord &)>;

    class Logger
    {
    private:
        std::string m_Name;
        LogLevel m_Level;
        LogHandler m_Handler;

    public:
        ETERNAL_CORE_API explicit Logger(std::string name, LogLevel level, LogHandler handler);

        ETERNAL_CORE_API const std::string &GetName() const;
        ETERNAL_CORE_API LogLevel GetLevel() const;
        ETERNAL_CORE_API void SetLevel(LogLevel level);
        ETERNAL_CORE_API bool IsEnabled(LogLevel level) const;

        template<typename... Args>
        void Log(LogLevel level, std::format_string<Args...> format, Args &&...args)
        {
            if (!IsEnabled(level))
            {
                return;
            }
            auto message = std::format(format, std::forward<Args>(args)...);
            auto record = LogRecord(m_Name, m_Level, message);
            m_Handler(record);
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
}
