#include "WindowClass.h"

#include <Windows.h>

#include "Utils.h"

namespace
{
    using namespace Eternal;

    EventBuffer &GetEventBuffer(HWND window)
    {
        auto data = GetWindowLongPtrW(window, GWLP_USERDATA);
        return *CastIntToPtr<EventBuffer>(data);
    }

    EventBuffer &SetEventBuffer(HWND window, LPARAM lparam)
    {
        auto &settings = *CastIntToPtr<CREATESTRUCT>(lparam);
        auto *data = settings.lpCreateParams;
        auto ptr = reinterpret_cast<LONG_PTR>(data);
        SetWindowLongPtrW(window, GWLP_USERDATA, ptr);
        return *static_cast<EventBuffer *>(data);
    }

    EventBuffer &GetOrSetEventBuffer(const WindowMessage &message)
    {
        if (message.Type == WM_CREATE)
        {
            return SetEventBuffer(message.Window, message.Lparam);
        }
        return GetEventBuffer(message.Window);
    }

    LRESULT CALLBACK ProcessMessage(HWND window, UINT type, WPARAM wparam, LPARAM lparam)
    {
        auto message = WindowMessage{
            .Window = window,
            .Type = type,
            .Wparam = wparam,
            .Lparam = lparam,
        };
        auto &events = GetOrSetEventBuffer(message);
        return ProcessWindowMessage(message, events);
    }
}

namespace Eternal
{
    WindowClass::Deleter::Deleter(HINSTANCE instance):
        m_Instance(instance)
    {
    }

    void WindowClass::Deleter::operator()(LPCWSTR className) const
    {
        auto success = UnregisterClassW(className, m_Instance);
        assert(success == TRUE);
    }

    WindowClass::WindowClass(HINSTANCE instance, LPCWSTR className):
        m_Instance(instance),
        m_ClassName(className, Deleter(instance))
    {
    }

    HWND WindowClass::Instanciate(const WindowSettings &settings, EventBuffer &events)
    {
        auto options = DWORD(0);
        const auto *className = m_ClassName.get();
        auto title = ToUtf16(settings.Title);
        auto style = WS_OVERLAPPEDWINDOW;
        auto x = static_cast<int>(settings.Position[0]);
        auto y = static_cast<int>(settings.Position[1]);
        auto width = static_cast<int>(settings.Size[0]);
        auto height = static_cast<int>(settings.Size[1]);
        auto *parent = HWND(nullptr);
        auto *menu = HMENU(nullptr);
        auto *window = CreateWindowExW(options, className, title.c_str(), style, x, y, width, height, parent, menu, m_Instance, &events);
        if (window == nullptr)
        {
            throw LastErrorToException("Failed to create window");
        }
        return window;
    }

    WindowClass CreateWindowClass(HINSTANCE instance, std::string_view name)
    {
        auto wname = ToUtf16(name);
        auto settings = WNDCLASSW{
            .lpfnWndProc = &ProcessMessage,
            .hInstance = instance,
            .lpszClassName = wname.c_str(),
        };
        auto atom = RegisterClassW(&settings);
        if (atom == 0)
        {
            throw LastErrorToException("Failed to create window class");
        }
        const auto *className = CastIntToPtr<const wchar_t>(atom);
        return WindowClass(instance, className);
    }
}
