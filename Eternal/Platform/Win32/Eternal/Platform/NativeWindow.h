#pragma once

#include <memory>

#include <Eternal/Core/Window.h>

namespace Eternal
{
    std::unique_ptr<WindowClass> CreateNativeWindowClass(const std::string &name);
}
