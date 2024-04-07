#pragma once

#include <span>
#include <string>
#include <string_view>

#include <Eternal/Core/Math/Types.h>

#include "WindowEvents.h"
#include "WindowHandle.h"

namespace Eternal
{
    using WindowId = std::size_t;

    struct WindowPrivate
    {
        WindowId Id;
        WindowHandle Handle;
        std::string Title;
        Vector2 Position;
        Vector2 Size;
        std::vector<WindowEvent> Events;
    };

    WindowPrivate CreateWindowPrivate(WindowId id, WindowHandle handle, const WindowSettings &settings);
    void PollWindowPrivate(WindowPrivate &window);

    class WindowRef
    {
    private:
        const WindowPrivate *m_Window;

    public:
        ETERNAL_CORE_API explicit WindowRef(const WindowPrivate &window);

        ETERNAL_CORE_API WindowId GetId() const;
        ETERNAL_CORE_API void *GetNativeHandle() const;
        ETERNAL_CORE_API std::span<const WindowEvent> GetEvents() const;
        ETERNAL_CORE_API std::string_view GetTitle() const;
        ETERNAL_CORE_API void SetTitle(std::string_view title);
        ETERNAL_CORE_API Vector2 GetPosition() const;
        ETERNAL_CORE_API void SetPosition(Vector2 position);
        ETERNAL_CORE_API Vector2 GetSize() const;
        ETERNAL_CORE_API void Resize(Vector2 size);
    };
}
