#include "WindowClass.h"

#include <Eternal/Platform/Win32/Utils.h>

namespace
{
    using namespace Eternal;

    WindowListener &GetListener(HWND window)
    {
        auto data = GetWindowLongPtrW(window, GWLP_USERDATA);
        return *CastIntToPtr<WindowListener *>(data);
    }

    WindowListener &SetListener(HWND window, LPARAM lparam)
    {
        auto &settings = *CastIntToPtr<CREATESTRUCT *>(lparam);

        auto *data = settings.lpCreateParams;
        auto ptr = reinterpret_cast<LONG_PTR>(data);

        SetWindowLongPtrW(window, GWLP_USERDATA, ptr);

        return *static_cast<WindowListener *>(data);
    }

    WindowListener &GetOrSetListener(HWND window, UINT type, LPARAM lparam)
    {
        if (type == WM_CREATE)
        {
            return SetListener(window, lparam);
        }

        return GetListener(window);
    }

    LRESULT CALLBACK ProcessMessage(HWND window, UINT type, WPARAM wparam, LPARAM lparam)
    {
        auto &listener = GetOrSetListener(window, type, lparam);
        auto message = NativeWindowMessage{window, type, wparam, lparam};

        return ProcessNativeWindowMessage(listener, message);
    }
}

namespace Eternal
{
    void WindowClass::Deleter::operator()(LPCWSTR className) const
    {
        auto success = UnregisterClassW(className, Instance);
        assert(success == TRUE);
    }

    WindowClass::WindowClass(HINSTANCE instance, LPCWSTR className):
        m_Instance(instance),
        m_ClassName(className, Deleter{instance})
    {
    }

    NativeWindow WindowClass::Instanciate(const WindowSettings &settings, WindowListener listener)
    {
        auto options = DWORD(0);
        auto title = ToUtf16(settings.Title);
        auto style = WS_OVERLAPPEDWINDOW;
        auto x = static_cast<int>(settings.Position[0]);
        auto y = static_cast<int>(settings.Position[1]);
        auto width = static_cast<int>(settings.Size[0]);
        auto height = static_cast<int>(settings.Size[1]);
        auto *parent = HWND(nullptr);
        auto *menu = HMENU(nullptr);

        auto ptr = std::make_unique<WindowListener>(std::move(listener));

        auto *window = CreateWindowExW(options, m_ClassName.get(), title.c_str(), style, x, y, width, height, parent, menu, m_Instance, ptr.get());

        if (window == nullptr)
        {
            throw LastErrorToException("Failed to create window");
        }

        return NativeWindow(window, std::move(ptr));
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

        const auto *className = CastIntToPtr<const wchar_t *>(atom);

        return WindowClass(instance, className);
    }
}
