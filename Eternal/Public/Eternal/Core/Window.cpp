#include "Window.h"

#include <cassert>
#include <stdexcept>

namespace
{
    using namespace Eternal;

    class WindowPropertyListener : public WindowListener
    {
    private:
        WindowProperties &m_Properties;

    public:
        explicit WindowPropertyListener(WindowProperties &properties):
            m_Properties(properties)
        {
        }

        void SetTitle(const std::string &title) override
        {
            m_Properties.Title = title;
        }

        void Resize(const Vector2 &size) override
        {
            m_Properties.Size = size;
        }

        void Close() override
        {
            m_Properties.Closed = true;
        }
    };

    std::unique_ptr<WindowProperties> CreateWindowProperties(const WindowSettings &settings)
    {
        auto properties = std::make_unique<WindowProperties>();
        properties->Title = settings.Title;
        properties->Size = settings.Size;
        return properties;
    }
}

namespace Eternal
{
    Window::Window(std::size_t id, WindowProperties &properties, WindowHandle &handle):
        m_Id(id),
        m_Properties(properties),
        m_Handle(handle)
    {
    }

    std::size_t Window::GetId() const
    {
        return m_Id;
    }

    const std::string &Window::GetTitle() const
    {
        return m_Properties.Title;
    }

    const Vector2 &Window::GetSize() const
    {
        return m_Properties.Size;
    }

    bool Window::IsClosed() const
    {
        return m_Properties.Closed;
    }

    void *Window::GetNativeHandle() const
    {
        return m_Handle.AsRawPtr();
    }

    WindowRegistry::WindowRegistry(std::unique_ptr<WindowClass> windowClass):
        m_WindowClass(std::move(windowClass))
    {
    }

    WindowHolder &WindowRegistry::Add(const WindowSettings &settings)
    {
        auto properties = CreateWindowProperties(settings);
        auto listener = std::make_unique<WindowPropertyListener>(*properties);
        auto handle = m_WindowClass->Instanciate(settings, std::move(listener));
        auto id = m_IdGenerator.Next();
        auto interface = std::make_unique<Window>(id, *properties, *handle);
        auto holder = WindowHolder{std::move(properties), std::move(handle), std::move(interface)};
        auto [i, inserted] = m_Windows.emplace(id, std::move(holder));
        assert(inserted);
        return i->second;
    }

    void WindowRegistry::Remove(std::size_t id)
    {
        auto i = m_Windows.find(id);
        if (i == m_Windows.end())
        {
            throw std::invalid_argument("Window ID does not exists");
        }
        m_Windows.erase(i);
        m_IdGenerator.Recycle(id);
    }

    void WindowRegistry::Update()
    {
        for (const auto &[id, window] : m_Windows)
        {
            window.Properties->Closed = false;
            window.Handle->Poll();
        }
    }

    WindowManager::WindowManager(WindowRegistry &windows):
        m_Windows(windows)
    {
    }

    Window &WindowManager::AddWindow(const WindowSettings &settings)
    {
        auto &window = m_Windows.Add(settings);
        return *window.Interface;
    }

    void WindowManager::RemoveWindow(std::size_t id)
    {
        m_Windows.Remove(id);
    }
}
