#include "WindowClass.h"

#include "Utils.h"

namespace
{
    using namespace Eternal;

    HWND CreateNativeWindowHandle(HINSTANCE instance, LPCWSTR className, const WindowSettings &settings, EventBuffer &events)
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

        auto *window = CreateWindowExW(options, className, title.c_str(), style, x, y, width, height, parent, menu, instance, &events);

        if (window == nullptr)
        {
            throw LastErrorToException("Failed to create window");
        }

        return window;
    }

    EventBuffer &GetEventBufferr(HWND window)
    {
        auto data = GetWindowLongPtrW(window, GWLP_USERDATA);
        return *CastIntToPtr<EventBuffer>(data);
    }

    EventBuffer &SetEventBufferr(HWND window, LPARAM lparam)
    {
        auto &settings = *CastIntToPtr<CREATESTRUCT>(lparam);
        auto *data = settings.lpCreateParams;
        auto ptr = reinterpret_cast<LONG_PTR>(data);
        SetWindowLongPtrW(window, GWLP_USERDATA, ptr);
        return *static_cast<EventBuffer *>(data);
    }

    EventBuffer &GetOrSetEventBufferr(HWND window, UINT type, LPARAM lparam)
    {
        if (type == WM_CREATE)
        {
            return SetEventBufferr(window, lparam);
        }
        return GetEventBufferr(window);
    }

    void OnSetTitle(LPARAM lparam, EventBuffer &events)
    {
        const auto *wtitle = CastIntToPtr<const wchar_t>(lparam);
        auto title = ToUtf8(wtitle);
        auto e = WindowRename(std::move(title));
        events.Add(std::move(e));
    }

    void OnMove(LPARAM lparam, EventBuffer &events)
    {
        auto x = static_cast<float>(LOWORD(lparam));
        auto y = static_cast<float>(HIWORD(lparam));
        auto size = Vector2(x, y);
        auto e = WindowMove(size);
        events.Add(e);
    }

    void OnResize(LPARAM lparam, EventBuffer &events)
    {
        auto width = static_cast<float>(LOWORD(lparam));
        auto height = static_cast<float>(HIWORD(lparam));
        auto size = Vector2(width, height);
        auto e = WindowResize(size);
        events.Add(e);
    }

    void OnClose(EventBuffer &events)
    {
        auto e = WindowClose();
        events.Add(e);
    }

    LRESULT CALLBACK ProcessMessage(HWND window, UINT type, WPARAM wparam, LPARAM lparam)
    {
        auto &events = GetOrSetEventBufferr(window, type, lparam);

        switch (type)
        {
        case WM_SETTEXT:
            OnSetTitle(lparam, events);
            break;
        case WM_MOVE:
            OnMove(lparam, events);
            return 0;
        case WM_SIZE:
            OnResize(lparam, events);
            return 0;
        case WM_CLOSE:
            OnClose(events);
            return 0;
        default:
            break;
        }

        return DefWindowProcW(window, type, wparam, lparam);
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

    WindowClass::WindowClass(GuiThread guiThread, HINSTANCE instance, LPCWSTR className):
        m_GuiThread(std::move(guiThread)),
        m_Instance(instance),
        m_ClassName(className, Deleter(instance))
    {
    }

    NativeWindowHandle WindowClass::Instanciate(const WindowSettings &settings)
    {
        auto events = std::make_unique<EventBuffer>();
        auto createHandle = [&] { return CreateNativeWindowHandle(m_Instance, m_ClassName.get(), settings, *events); };
        auto handle = m_GuiThread.Run(createHandle);
        return NativeWindowHandle(m_GuiThread, handle, std::move(events));
    }

    WindowClass CreateWindowClass(GuiThread guiThread, HINSTANCE instance, std::string_view name)
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

        return WindowClass(std::move(guiThread), instance, className);
    }
}
