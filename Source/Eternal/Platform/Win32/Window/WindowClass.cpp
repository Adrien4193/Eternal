#include "WindowClass.h"

#include "Utils.h"

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

    void OnSetTitle(LPARAM lparam, WindowListener &listener)
    {
        const auto *wtitle = CastIntToPtr<const wchar_t *>(lparam);
        auto title = ToUtf8(wtitle);
        listener(WindowRename(std::move(title)));
    }

    void OnMove(LPARAM lparam, WindowListener &listener)
    {
        auto x = static_cast<float>(LOWORD(lparam));
        auto y = static_cast<float>(HIWORD(lparam));
        auto size = Vector2(x, y);
        listener(WindowMove(size));
    }

    void OnResize(LPARAM lparam, WindowListener &listener)
    {
        auto width = static_cast<float>(LOWORD(lparam));
        auto height = static_cast<float>(HIWORD(lparam));
        auto size = Vector2(width, height);
        listener(WindowResize(size));
    }

    void OnClose(WindowListener &listener)
    {
        listener(WindowClose());
    }

    void OnMouse(WindowListener &listener, const RAWMOUSE &mouse)
    {
        (void)mouse;
        listener(WindowInput());
    }

    void OnKeyboard(WindowListener &listener, const RAWKEYBOARD &keyboard)
    {
        (void)keyboard;
        listener(WindowInput());
    }

    void OnHid(WindowListener &listener, const RAWHID &hid)
    {
        (void)hid;
        listener(WindowInput());
    }

    void OnInput(WindowListener &listener, LPARAM lparam)
    {
        static constexpr auto headerSize = sizeof(RAWINPUTHEADER);

        auto handle = CastIntToPtr<HRAWINPUT>(lparam);

        auto size = UINT(0);

        auto status = GetRawInputData(handle, RID_INPUT, nullptr, &size, headerSize);

        if (status == UINT(-1))
        {
            return;
        }

        auto bytes = std::vector<char>(size);

        auto data = bytes.data();

        auto written = GetRawInputData(handle, RID_INPUT, data, &size, headerSize);

        if (written != size)
        {
            return;
        }

        const auto &input = *reinterpret_cast<const RAWINPUT *>(data);

        switch (input.header.dwType)
        {
        case RIM_TYPEMOUSE:
            OnMouse(listener, input.data.mouse);
            break;
        case RIM_TYPEKEYBOARD:
            OnKeyboard(listener, input.data.keyboard);
            break;
        case RIM_TYPEHID:
            OnHid(listener, input.data.hid);
            break;
        default:
            break;
        }
    }

    LRESULT CALLBACK ProcessMessage(HWND window, UINT type, WPARAM wparam, LPARAM lparam)
    {
        auto &listener = GetOrSetListener(window, type, lparam);

        switch (type)
        {
        case WM_SETTEXT:
            OnSetTitle(lparam, listener);
            break;
        case WM_MOVE:
            OnMove(lparam, listener);
            return 0;
        case WM_SIZE:
            OnResize(lparam, listener);
            return 0;
        case WM_CLOSE:
            OnClose(listener);
            return 0;
        case WM_INPUT:
            OnInput(listener, lparam);
            break;
        default:
            break;
        }

        return DefWindowProcW(window, type, wparam, lparam);
    }
}

namespace Eternal
{
    void NativeWindow::Deleter::operator()(HWND handle) const
    {
        auto success = DestroyWindow(handle);
        assert(success == TRUE);
    }

    NativeWindow::NativeWindow(HWND handle, std::unique_ptr<WindowListener> listener):
        m_Handle(handle),
        m_Listener(std::move(listener))
    {
    }

    HWND NativeWindow::GetHandle() const
    {
        return m_Handle.get();
    }

    void NativeWindow::Show(int code)
    {
        auto previousVisibility = ShowWindow(m_Handle.get(), code);
        (void)previousVisibility;
    }

    void NativeWindow::SetTitle(std::string_view title)
    {
        auto wtitle = ToUtf16(title);
        auto success = SetWindowTextW(m_Handle.get(), wtitle.c_str());

        if (success == FALSE)
        {
            throw LastErrorToException("Failed to set window title");
        }
    }

    void NativeWindow::SetPosition(Vector2 position)
    {
        auto flags = SWP_NOSIZE | SWP_NOACTIVATE;
        auto width = static_cast<int>(position[0]);
        auto height = static_cast<int>(position[1]);

        auto success = SetWindowPos(m_Handle.get(), nullptr, width, height, 0, 0, flags);

        if (success == FALSE)
        {
            throw LastErrorToException("Failed to set window position");
        }
    }

    void NativeWindow::Resize(Vector2 size)
    {
        auto flags = SWP_NOMOVE | SWP_NOACTIVATE;
        auto width = static_cast<int>(size[0]);
        auto height = static_cast<int>(size[1]);

        auto success = SetWindowPos(m_Handle.get(), nullptr, 0, 0, width, height, flags);

        if (success == FALSE)
        {
            throw LastErrorToException("Failed to set window size");
        }
    }

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

        auto boxedListener = std::make_unique<WindowListener>(std::move(listener));

        auto *window = CreateWindowExW(options, m_ClassName.get(), title.c_str(), style, x, y, width, height, parent, menu, m_Instance, boxedListener.get());

        if (window == nullptr)
        {
            throw LastErrorToException("Failed to create window");
        }

        return NativeWindow(window, std::move(boxedListener));
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
