#pragma once

#include <memory>
#include <string>

#include <Eternal/Core/Window.h>
#include <Eternal/Math/Types.h>

namespace Eternal
{
    class WindowListener
    {
    public:
        virtual ~WindowListener() = default;

        virtual void SetTitle(const std::string &title) = 0;
        virtual void Resize(const Vector2 &size) = 0;
        virtual void Close() = 0;
    };

    class WindowClass
    {
    public:
        virtual ~WindowClass() = default;

        virtual std::unique_ptr<WindowHandle> Instanciate(const WindowSettings &settings, std::unique_ptr<WindowListener> listener) = 0;
    };
}
