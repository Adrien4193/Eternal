#pragma once

#include <functional>
#include <string_view>
#include <vector>

#include <Eternal/Core/Math/Types.h>

#include "WindowEvents.h"
#include "WindowSettings.h"

namespace Eternal
{
    struct WindowHandle
    {
        void *NativePtr;
        std::function<std::vector<WindowEvent>()> Poll;
        std::function<void()> Show;
        std::function<void(std::string_view)> SetTitle;
        std::function<void(Vector2)> SetPosition;
        std::function<void(Vector2)> Resize;
    };

    using WindowHandleFactory = std::function<WindowHandle(const WindowSettings &)>;
}
