#include "ConsoleLogger.h"

#include <iostream>

namespace Eternal
{
    void PrintLogRecord(const LogRecord &record)
    {
        auto data = FormatLogRecord(record);
        std::cout << data << '\n';
    }

    Logger CreateConsoleLogger(std::string name)
    {
        return Logger(std::move(name), LogLevel::Info, [](const auto &record) { PrintLogRecord(record); });
    }
}
