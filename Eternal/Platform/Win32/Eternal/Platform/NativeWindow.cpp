#include "NativeWindow.h"

#include <format>
#include <stdexcept>

namespace
{
    using namespace Eternal;

    std::runtime_error LastErrorToException(const std::string &message)
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
        auto ptr = value.data();
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
        auto ptr = value.data();
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

    WindowListener &GetListener(HWND window)
    {
        auto ptr = GetWindowLongPtrW(window, GWLP_USERDATA);
        return *reinterpret_cast<WindowListener *>(ptr);
    }

    WindowListener &SetListener(HWND window, LPARAM l)
    {
        auto settings = reinterpret_cast<CREATESTRUCT *>(l);
        auto data = settings->lpCreateParams;
        auto ptr = reinterpret_cast<LONG_PTR>(data);
        SetWindowLongPtrW(window, GWLP_USERDATA, ptr);
        return *reinterpret_cast<WindowListener *>(data);
    }

    WindowListener &GetOrSetListener(HWND window, UINT message, LPARAM l)
    {
        if (message != WM_CREATE)
        {
            return GetListener(window);
        }
        return SetListener(window, l);
    }

    void OnSetTitle(WindowListener &listener, LPARAM l)
    {
        auto wtitle = reinterpret_cast<LPCWSTR>(l);
        auto title = ToUtf8(wtitle);
        listener.OnSetTitle(std::move(title));
    }

    void OnResize(WindowListener &listener, LPARAM l)
    {
        auto width = LOWORD(l);
        auto height = HIWORD(l);
        auto size = WindowSize(static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height));
        listener.OnResize(size);
    }

    LRESULT CALLBACK ProcessMessage(HWND window, UINT message, WPARAM w, LPARAM l)
    {
        auto &listener = GetOrSetListener(window, message, l);
        switch (message)
        {
        case WM_SETTEXT:
            OnSetTitle(listener, l);
            return 0;
        case WM_SIZE:
            OnResize(listener, l);
            return 0;
        case WM_CLOSE:
            listener.OnClose();
            return 0;
        default:
            return DefWindowProcW(window, message, w, l);
        }
    }
}

namespace Eternal
{
    NativeWindowHandle::NativeWindowHandle(HWND handle, std::unique_ptr<WindowListener> listener):
        m_Handle(handle),
        m_Listener(std::move(listener))
    {
    }

    NativeWindowHandle::~NativeWindowHandle()
    {
        DestroyWindow(m_Handle);
    }

    void *NativeWindowHandle::AsRawPtr() const
    {
        return m_Handle;
    }

    void NativeWindowHandle::Poll()
    {
        auto message = MSG();
        while (PeekMessageW(&message, m_Handle, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }

    void NativeWindowHandle::Show()
    {
        ShowWindow(m_Handle, SW_SHOWNORMAL);
    }

    NativeWindowClass::NativeWindowClass(HINSTANCE instance, LPCWSTR className):
        m_Instance(instance),
        m_ClassName(className)
    {
    }

    NativeWindowClass::~NativeWindowClass()
    {
        UnregisterClassW(m_ClassName, m_Instance);
    }

    std::unique_ptr<WindowHandle> NativeWindowClass::Instanciate(const WindowSettings &settings, std::unique_ptr<WindowListener> listener)
    {
        auto options = DWORD(0);
        auto title = ToUtf16(settings.Title);
        auto style = WS_OVERLAPPEDWINDOW;
        auto x = CW_USEDEFAULT;
        auto y = CW_USEDEFAULT;
        auto width = static_cast<int>(settings.Size.Width);
        auto height = static_cast<int>(settings.Size.Height);
        auto parent = HWND(nullptr);
        auto menu = HMENU(nullptr);
        auto window = CreateWindowExW(options, m_ClassName, title.c_str(), style, x, y, width, height, parent, menu, m_Instance, listener.get());
        if (!window)
        {
            throw LastErrorToException("Failed to create window");
        }
        return std::make_unique<NativeWindowHandle>(window, std::move(listener));
    }

    std::unique_ptr<WindowClass> CreateWindowClass(HINSTANCE instance, const std::string &name)
    {
        auto wname = ToUtf16(name);
        auto settings = WNDCLASSW();
        settings.lpfnWndProc = &ProcessMessage;
        settings.hInstance = instance;
        settings.lpszClassName = wname.c_str();
        auto atom = RegisterClassW(&settings);
        if (!atom)
        {
            throw LastErrorToException("Failed to create window class");
        }
        auto className = reinterpret_cast<LPCWSTR>(atom);
        return std::make_unique<NativeWindowClass>(instance, className);
    }

    std::unique_ptr<WindowClass> CreateWindowClass(const std::string &name)
    {
        auto instance = GetModuleHandleW(nullptr);
        return CreateWindowClass(instance, name);
    }
}
