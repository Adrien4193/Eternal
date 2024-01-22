#pragma once

#include "Application.h"

namespace Eternal
{
    struct ApplicationSettings
    {
    };

    ETERNAL_EXPORT Application CreateApplication(const ApplicationSettings &settings);
}
