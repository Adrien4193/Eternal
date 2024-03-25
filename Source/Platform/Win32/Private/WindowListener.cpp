#include "WindowListener.h"

#include "Utils.h"

namespace
{
    using namespace Eternal;

    void OnSetTitle(LPARAM lparam, EventBuffer &events)
    {
        const auto *wtitle = CastIntToPtr<const wchar_t>(lparam);
        auto title = ToUtf8(wtitle);
        auto e = WindowRename(std::move(title));
        events.Push(std::move(e));
    }

    void OnMove(LPARAM lparam, EventBuffer &events)
    {
        auto x = static_cast<float>(LOWORD(lparam));
        auto y = static_cast<float>(HIWORD(lparam));
        auto size = Vector2(x, y);
        auto e = WindowMove(size);
        events.Push(e);
    }

    void OnResize(LPARAM lparam, EventBuffer &events)
    {
        auto width = static_cast<float>(LOWORD(lparam));
        auto height = static_cast<float>(HIWORD(lparam));
        auto size = Vector2(width, height);
        auto e = WindowResize(size);
        events.Push(e);
    }

    void OnClose(EventBuffer &events)
    {
        auto e = WindowClose();
        events.Push(e);
    }
}

namespace Eternal
{
    LRESULT ProcessWindowMessage(const WindowMessage &message, EventBuffer &events)
    {
        switch (message.Type)
        {
        case WM_SETTEXT:
            OnSetTitle(message.Lparam, events);
            break;
        case WM_MOVE:
            OnMove(message.Lparam, events);
            return 0;
        case WM_SIZE:
            OnResize(message.Lparam, events);
            return 0;
        case WM_CLOSE:
            OnClose(events);
            return 0;
        default:
            break;
        }
        return DefWindowProcW(message.Window, message.Type, message.Wparam, message.Lparam);
    }
}
