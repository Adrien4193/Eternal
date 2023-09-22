#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <Eternal/Math/Types.h>

#include <Eternal/Utils/IdGenerator.h>

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

    class WindowClass
    {
    public:
        virtual ~WindowClass() = default;

        virtual std::unique_ptr<WindowHandle> Instanciate(const WindowSettings &settings, std::unique_ptr<WindowListener> listener) = 0;
    };

    class Window
    {
    private:
        std::size_t m_Id;
        WindowProperties &m_Properties;
        WindowHandle &m_Handle;

    public:
        explicit Window(std::size_t id, WindowProperties &properties, WindowHandle &handle);

        std::size_t GetId() const;
        const std::string &GetTitle() const;
        const Vector2 &GetSize() const;
        bool IsClosed() const;
        void *GetNativeHandle() const;

        template<typename T>
        T As() const
        {
            return static_cast<T>(GetNativeHandle());
        }
    };

    struct WindowHolder
    {
        std::unique_ptr<WindowProperties> Properties;
        std::unique_ptr<WindowHandle> Handle;
        std::unique_ptr<Window> Interface;
    };

    class WindowRegistry
    {
    private:
        std::unique_ptr<WindowClass> m_WindowClass;
        std::unordered_map<std::size_t, WindowHolder> m_Windows;
        IdGenerator<std::size_t> m_IdGenerator;

    public:
        explicit WindowRegistry(std::unique_ptr<WindowClass> windowClass);

        WindowHolder &Add(const WindowSettings &settings);
        void Remove(std::size_t id);
        void Update();
    };

    class WindowManager
    {
    private:
        WindowRegistry &m_Windows;

    public:
        explicit WindowManager(WindowRegistry &windows);

        Window &AddWindow(const WindowSettings &settings);
        void RemoveWindow(std::size_t id);
    };
}
