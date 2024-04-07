#pragma once

#include <string_view>

#include <Eternal/Core/Math/Types.h>

namespace Eternal
{
    struct WindowSettings
    {
        std::string_view Title;
        Vector2 Position;
        Vector2 Size;
    };
}
