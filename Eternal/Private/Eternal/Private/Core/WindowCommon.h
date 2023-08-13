#pragma once

#include <memory>
#include <string>

#include <Eternal/Core/Window.h>

namespace Eternal
{
    class WindowListener
    {
    public:
        virtual ~WindowListener() = default;

        virtual void OnSetTitle(const std::string &title) = 0;
        virtual void OnResize(const WindowSize &size) = 0;
        virtual void OnClose() = 0;
    };

    class WindowHandle
    {
    public:
        virtual ~WindowHandle() = default;

        virtual void *AsRawPtr() const = 0;
        virtual void Poll() = 0;
        virtual void Show() = 0;
    };

    class WindowClass
    {
    public:
        virtual ~WindowClass() = default;

        virtual std::unique_ptr<WindowHandle> Instanciate(const WindowSettings &settings, std::unique_ptr<WindowListener> listener) = 0;
    };
}
