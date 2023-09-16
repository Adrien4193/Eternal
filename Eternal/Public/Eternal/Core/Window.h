#pragma once

#include <memory>
#include <string>

#include <Eternal/Math/Types.h>

namespace Eternal
{
    struct WindowSettings
    {
        std::string Title;
        Vector2 Size = {};
    };

    struct WindowProperties
    {
        std::string Title;
        Vector2 Size = {};
        bool Closed = false;
    };

    class WindowHandle
    {
    public:
        virtual ~WindowHandle() = default;

        virtual void *AsRawPtr() const = 0;
        virtual void Poll() = 0;
    };

    class Window
    {
    private:
        WindowHandle &m_Handle;
        WindowProperties &m_Properties;

    public:
        explicit Window(WindowHandle &handle, WindowProperties &properties);

        void *GetNativeHandle() const;
        const std::string &GetTitle() const;
        const Vector2 &GetSize() const;
    };
}
