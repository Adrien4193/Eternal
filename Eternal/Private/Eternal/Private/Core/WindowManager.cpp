#include "WindowManager.h"

#include <Eternal/Platform/NativeWindow.h>

namespace
{
    using namespace Eternal;

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
    WindowPropertyListener::WindowPropertyListener(WindowProperties &properties):
        m_Properties(properties)
    {
    }

    void WindowPropertyListener::SetTitle(const std::string &title)
    {
        m_Properties.Title = title;
    }

    void WindowPropertyListener::Resize(const Vector2 &size)
    {
        m_Properties.Size = size;
    }

    void WindowPropertyListener::Close()
    {
        m_Properties.Closed = true;
    }

    WindowManager::WindowManager(std::unique_ptr<WindowClass> cls, WindowHolder window):
        m_Cls(std::move(cls)),
        m_Window(std::move(window))
    {
    }

    Window &WindowManager::GetWindow() const
    {
        return *m_Window.Window;
    }

    bool WindowManager::IsClosed() const
    {
        return m_Window.Properties->Closed;
    }

    void WindowManager::Update()
    {
        m_Window.Handle->Poll();
    }

    std::unique_ptr<WindowManager> CreateWindowManager(const WindowSettings &settings)
    {
        auto cls = CreateNativeWindowClass("Eternal");
        auto properties = CreateWindowProperties(settings);
        auto listener = std::make_unique<WindowPropertyListener>(*properties);
        auto handle = cls->Instanciate(settings, std::move(listener));
        auto window = std::make_unique<Window>(*handle, *properties);
        auto holder = WindowHolder{std::move(properties), std::move(handle), std::move(window)};
        return std::make_unique<WindowManager>(std::move(cls), std::move(holder));
    }
}
