#include "Utils.h"

#include <errhandlingapi.h>
#include <stringapiset.h>

#include <format>

namespace Eternal
{
    std::runtime_error LastErrorToException(std::string_view message)
    {
        auto code = GetLastError();
        auto description = std::format("{} (code = {})", message, code);
        return std::runtime_error(description);
    }

    std::string ToUtf8(std::wstring_view value)
    {
        if (value.empty())
        {
            return {};
        }
        const auto *ptr = value.data();
        auto size = static_cast<int>(value.size());
        auto required = WideCharToMultiByte(CP_UTF8, 0, ptr, size, nullptr, 0, nullptr, nullptr);
        if (required <= 0)
        {
            throw LastErrorToException("Conversion preparation to UTF-16 failed");
        }
        auto result = std::string(required, '\0');
        auto written = WideCharToMultiByte(CP_UTF8, 0, ptr, size, result.data(), required, nullptr, nullptr);
        if (written != required)
        {
            throw LastErrorToException("Conversion to UTF-16 failed");
        }
        return result;
    }

    std::wstring ToUtf16(std::string_view value)
    {
        if (value.empty())
        {
            return {};
        }
        const auto *ptr = value.data();
        auto size = static_cast<int>(value.size());
        auto required = MultiByteToWideChar(CP_UTF8, 0, ptr, size, nullptr, 0);
        if (required <= 0)
        {
            throw LastErrorToException("Conversion preparation to UTF-8 failed");
        }
        auto result = std::wstring(required, L'\0');
        auto written = MultiByteToWideChar(CP_UTF8, 0, ptr, size, result.data(), required);
        if (written != required)
        {
            throw LastErrorToException("Conversion to UTF-8 failed");
        }
        return result;
    }
}
