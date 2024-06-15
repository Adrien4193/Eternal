#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

namespace Eternal
{
    std::runtime_error LastErrorToException(std::string_view message);
    std::string FormatLastError(std::string_view message);
    std::string ToUtf8(std::wstring_view value);
    std::wstring ToUtf16(std::string_view value);

    template<typename PtrType, typename IntegerType>
    PtrType CastIntToPtr(IntegerType integer)
    {
        return reinterpret_cast<PtrType>(integer); // NOLINT(performance-no-int-to-ptr)
    }
}
