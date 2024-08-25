#include "RawInput.h"

#include <vector>

#include "Utils.h"

namespace
{
    using namespace Eternal;

    WindowInput ParseMouse(const RAWMOUSE &mouse)
    {
        (void)mouse;
        return WindowInput();
    }

    WindowInput ParseKeyboard(const RAWKEYBOARD &keyboard)
    {
        (void)keyboard;
        return WindowInput();
    }

    WindowInput ParseHid(const RAWHID &hid)
    {
        (void)hid;
        return WindowInput();
    }
}

namespace Eternal
{
    WindowInput ParseRawInput(LPARAM lparam)
    {
        static constexpr auto headerSize = sizeof(RAWINPUTHEADER);

        auto handle = CastIntToPtr<HRAWINPUT>(lparam);

        auto size = UINT(0);

        auto status = GetRawInputData(handle, RID_INPUT, nullptr, &size, headerSize);

        if (status == UINT(-1))
        {
            throw WindowException("Failed to get raw input data size");
        }

        auto bytes = std::vector<char>(size);

        auto data = bytes.data();

        auto written = GetRawInputData(handle, RID_INPUT, data, &size, headerSize);

        if (written != size)
        {
            throw WindowException("Failed to get raw input data");
        }

        const auto &input = *reinterpret_cast<const RAWINPUT *>(data);

        switch (input.header.dwType)
        {
        case RIM_TYPEMOUSE:
            return ParseMouse(input.data.mouse);
        case RIM_TYPEKEYBOARD:
            return ParseKeyboard(input.data.keyboard);
        case RIM_TYPEHID:
            return ParseHid(input.data.hid);
        default:
            throw WindowException("Unknown raw input type");
        }
    }
}
