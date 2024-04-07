#pragma once

#include "Logger.h"

namespace Eternal
{
    ETERNAL_CORE_API void PrintLogRecord(const LogRecord &record);
    ETERNAL_CORE_API Logger CreateConsoleLogger(std::string name);
}
