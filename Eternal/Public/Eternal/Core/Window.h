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

    class WindowListener
    {
    public:
        virtual ~WindowListener() = default;

        virtual void SetTitle(const std::string &title) = 0;
        virtual void Resize(const Vector2 &size) = 0;
        virtual void Close() = 0;
    };

    class WindowPropertyListener : public WindowListener
    {
    private:
        WindowProperties &m_Properties;

    public:
        explicit WindowPropertyListener(WindowProperties &properties);

        void SetTitle(const std::string &title) override;
        void Resize(const Vector2 &size) override;
        void Close() override;
    };

    class WindowClass
    {
    public:
        virtual ~WindowClass() = default;

        virtual std::unique_ptr<WindowHandle> Instanciate(const WindowSettings &settings, std::unique_ptr<WindowListener> listener) = 0;
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
