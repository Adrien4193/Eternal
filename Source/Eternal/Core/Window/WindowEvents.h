#pragma once

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
}
