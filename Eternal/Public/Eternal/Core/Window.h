#pragma once

#include <cstdint>
#include <string>

namespace Eternal
{
    struct WindowSize
    {
        std::uint32_t Width = 0;
        std::uint32_t Height = 0;
    };

    struct WindowSettings
    {
        std::string Title;
        WindowSize Size;
    };

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void *GetNativeHandle() const = 0;
        virtual const std::string &GetTitle() const = 0;
        virtual const WindowSize &GetSize() const = 0;
        virtual bool IsClosed() const = 0;
    };
}
