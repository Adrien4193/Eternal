#pragma once

#include "Application.h"

#include <Eternal/Core/Logging/Logger.h>
#include <Eternal/Core/Window/WindowHandle.h>

namespace Eternal
{
    struct ApplicationSettings
    {
        Logger Logger;
        WindowHandleFactory WindowHandleFactory;
    };

    ETERNAL_CORE_API Application CreateApplication(ApplicationSettings settings);
}
