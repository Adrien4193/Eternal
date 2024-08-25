#include "NativeWindow.h"

#include "RawInput.h"
#include "Utils.h"

namespace
{
    using namespace Eternal;

    void OnSetTitle(const WindowListener &listener, LPARAM lparam)
    {
        const auto *wtitle = CastIntToPtr<const wchar_t *>(lparam);
        auto title = ToUtf8(wtitle);
        listener(WindowRename(std::move(title)));
    }

    void OnMove(const WindowListener &listener, LPARAM lparam)
    {
        auto x = static_cast<float>(LOWORD(lparam));
        auto y = static_cast<float>(HIWORD(lparam));

        auto size = Vector2(x, y);

        listener(WindowMove(size));
    }

    void OnResize(const WindowListener &listener, LPARAM lparam)
    {
        auto width = static_cast<float>(LOWORD(lparam));
        auto height = static_cast<float>(HIWORD(lparam));

        auto size = Vector2(width, height);

        listener(WindowResize(size));
    }

    void OnClose(const WindowListener &listener)
    {
        listener(WindowClose());
    }

    void OnInput(const WindowListener &listener, LPARAM lparam)
    {
        try
        {
            auto event = ParseRawInput(lparam);
            listener(std::move(event));
        }
        catch (const WindowException &e)
        {
            listener(e);
        }
        catch (...)
        {
            listener(WindowException("Unexpected window error"));
        }
    }
}

namespace Eternal
{
    LRESULT ProcessNativeWindowMessage(const WindowListener &listener, const NativeWindowMessage &message)
    {
        switch (message.Type)
        {
        case WM_SETTEXT:
            OnSetTitle(listener, message.Lparam);
            break;
        case WM_MOVE:
            OnMove(listener, message.Lparam);
            return 0;
        case WM_SIZE:
            OnResize(listener, message.Lparam);
            return 0;
        case WM_CLOSE:
            OnClose(listener);
            return 0;
        case WM_INPUT:
            OnInput(listener, message.Lparam);
            break;
        default:
            break;
        }

        return DefWindowProcW(message.Window, message.Type, message.Wparam, message.Lparam);
    }

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
        ShowWindow(m_Handle.get(), code);
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
}
