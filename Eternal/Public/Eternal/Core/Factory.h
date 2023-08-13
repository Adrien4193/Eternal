#pragma once

#include <memory>
#include <string>

#include "Application.h"

namespace Eternal
{
    std::unique_ptr<Application> CreateApplication(const std::string &name);
}
