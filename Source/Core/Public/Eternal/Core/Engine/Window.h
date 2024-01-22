#pragma once

#include <functional>
#include <memory>
#include <string>
#include <string_view>

#include <Eternal/Core/Math/Types.h>
#include <Eternal/Core/Utils/EventQueue.h>

namespace Eternal
{
    using WindowId = std::size_t;

    using WindowEvent = std::any;

    struct WindowRename
    {
        std::string_view Title;
    };

    struct WindowMove
    {
        Vector2 Position;
    };

    struct WindowResize
    {
        Vector2 Size;
    };

    struct WindowClose
    {
    };

    struct WindowProperties
    {
        WindowId Id = 0;
        void *NativeHandle = nullptr;
        std::string Title;
        Vector2 Position = {};
        Vector2 Size = {};
        EventQueue Events;
        std::function<void(const WindowEvent &)> Send;
    };

    class Window
    {
    private:
        const WindowProperties &m_Properties;

    public:
        ETERNAL_EXPORT explicit Window(const WindowProperties &properties);
        ~Window() = default;

        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;
        Window(Window &&) = delete;
        Window &operator=(Window &&) = delete;

        ETERNAL_EXPORT WindowId GetId() const;
        ETERNAL_EXPORT void *GetNativeHandle() const;
        ETERNAL_EXPORT const std::string &GetTitle() const;
        ETERNAL_EXPORT void SetTitle(std::string_view title);
        ETERNAL_EXPORT const Vector2 &GetPosition() const;
        ETERNAL_EXPORT void SetPosition(const Vector2 &position);
        ETERNAL_EXPORT const Vector2 &GetSize() const;
        ETERNAL_EXPORT void Resize(const Vector2 &size);

        template<typename NativeHandleType>
        NativeHandleType As() const
        {
            return static_cast<NativeHandleType>(GetNativeHandle());
        }

        template<typename EventType, typename CallableType>
        void On(CallableType &&callable) const
        {
            m_Properties.Events.On<EventType>(std::forward<CallableType>(callable));
        }

        template<typename EventType, typename CallableType>
        void Once(CallableType &&callable) const
        {
            m_Properties.Events.Once<EventType>(std::forward<CallableType>(callable));
        }
    };
}
