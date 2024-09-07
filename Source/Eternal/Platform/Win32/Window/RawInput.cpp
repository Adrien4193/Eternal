#include "RawInput.h"

#include <vector>

#include <hidusage.h>

#include <Eternal/Platform/Win32/Utils.h>

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

    WindowInput Parse(const RAWINPUT &input)
    {
        switch (input.header.dwType)
        {
        case RIM_TYPEMOUSE:
            return ParseMouse(input.data.mouse);
        case RIM_TYPEKEYBOARD:
            return ParseKeyboard(input.data.keyboard);
        case RIM_TYPEHID:
            return ParseHid(input.data.hid);
        default:
            throw std::invalid_argument("Unknown raw input type");
        }
    }
}

namespace Eternal
{
    WindowInput ParseRawInput(LPARAM lparam)
    {
        static constexpr auto headerSize = UINT(sizeof(RAWINPUTHEADER));

        auto handle = CastIntToPtr<HRAWINPUT>(lparam);

        auto size = UINT(0);
        auto status = GetRawInputData(handle, RID_INPUT, nullptr, &size, headerSize);

        if (status == UINT(-1))
        {
            throw std::runtime_error("Failed to get raw input data size");
        }

        auto bytes = std::vector<char>(size);
        auto data = bytes.data();

        auto written = GetRawInputData(handle, RID_INPUT, data, &size, headerSize);

        if (written != size)
        {
            throw std::runtime_error("Failed to get raw input data");
        }

        const auto &input = *reinterpret_cast<const RAWINPUT *>(data);

        return Parse(input);
    }

    void RegisterMouseInputDevice(HWND window)
    {
        auto device = RAWINPUTDEVICE{
            .usUsagePage = HID_USAGE_PAGE_GENERIC,
            .usUsage = HID_USAGE_GENERIC_MOUSE,
            .dwFlags = RIDEV_DEVNOTIFY,
            .hwndTarget = window,
        };

        auto success = RegisterRawInputDevices(&device, 1, sizeof(device));

        if (success != TRUE)
        {
            throw LastErrorToException("Failed to register raw input device");
        }
    }
}
