#pragma once

#include <functional>
#include <span>
#include <string>
#include <string_view>

#include <Eternal/Core/Math/Types.h>

#include "WindowEvents.h"

namespace Eternal
{
    using WindowId = std::size_t;

    struct WindowSettings
    {
        std::string_view Title;
        Vector2 Position;
        Vector2 Size;
    };

    struct WindowHandle
    {
        void *NativePtr;
        std::function<std::vector<WindowEvent>()> Poll;
        std::function<void()> Show;
        std::function<void(std::string_view)> SetTitle;
        std::function<void(Vector2)> SetPosition;
        std::function<void(Vector2)> Resize;
    };

    using WindowFactory = std::function<WindowHandle(const WindowSettings &)>;

    struct WindowPrivate
    {
        WindowId Id;
        WindowHandle Handle;
        std::string Title;
        Vector2 Position;
        Vector2 Size;
        std::vector<WindowEvent> Events;
    };

    class Window
    {
    private:
        const WindowPrivate *m_Window;

    public:
        ETERNAL_CORE_API explicit Window(const WindowPrivate &window);

        ETERNAL_CORE_API WindowId GetId() const;
        ETERNAL_CORE_API void *GetNativeHandle() const;
        ETERNAL_CORE_API std::span<const WindowEvent> GetEvents() const;
        ETERNAL_CORE_API void Show();
        ETERNAL_CORE_API std::string_view GetTitle() const;
        ETERNAL_CORE_API void SetTitle(std::string_view title);
        ETERNAL_CORE_API Vector2 GetPosition() const;
        ETERNAL_CORE_API void SetPosition(Vector2 position);
        ETERNAL_CORE_API Vector2 GetSize() const;
        ETERNAL_CORE_API void Resize(Vector2 size);
    };
}
