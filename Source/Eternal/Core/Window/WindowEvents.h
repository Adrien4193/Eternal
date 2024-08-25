#pragma once

#include <stdexcept>
#include <string>
#include <variant>

#include <Eternal/Core/Math/Types.h>

namespace Eternal
{
    class WindowException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
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

    using WindowEvent = std::variant<WindowRename, WindowMove, WindowResize, WindowClose, WindowInput>;

    using WindowMessage = std::variant<WindowException, WindowEvent>;
}
