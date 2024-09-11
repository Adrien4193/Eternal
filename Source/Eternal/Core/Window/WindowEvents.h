#pragma once

#include <ranges>
#include <stdexcept>
#include <string>
#include <variant>

#include <Eternal/Core/Math/Types.h>

namespace Eternal
{
    struct WindowError
    {
        std::exception_ptr exception;
    };

    struct WindowRename
    {
        std::string Title;
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

    struct WindowInput
    {
    };

    using WindowEvent = std::variant<WindowError, WindowRename, WindowMove, WindowResize, WindowClose, WindowInput>;

    template<typename T>
    concept WindowEventHandler = requires(T callable, const WindowEvent &e) {
        { std::visit(callable, e) };
    };

    void OnWindowEvent(std::ranges::range auto &&events, WindowEventHandler auto &&handler)
    {
        for (const auto &event : events)
        {
            std::visit(handler, event);
        }
    }
}
