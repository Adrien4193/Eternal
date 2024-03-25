#pragma once

#include <memory>

#include <Eternal/Core/Utils/IdGenerator.h>

#include "Window.h"
#include "WindowSettings.h"

namespace Eternal
{
    struct WindowHolder
    {
        std::unique_ptr<WindowPrivate> WindowPrivate;
        std::unique_ptr<Window> Window;
    };

    class WindowManagerPrivate
    {
    private:
        WindowHandleFactory m_HandleFactory;
        IdGenerator<WindowId> m_IdGenerator;
        std::unordered_map<WindowId, WindowHolder> m_Windows;

    public:
        ETERNAL_CORE_API explicit WindowManagerPrivate(WindowHandleFactory handleFactory);

        ETERNAL_CORE_API Window &AddWindow(const WindowSettings &settings);
        ETERNAL_CORE_API void RemoveWindow(WindowId id);
        ETERNAL_CORE_API void PollWindows();
    };

    class WindowManager
    {
    private:
        WindowManagerPrivate &m_Windows;

    public:
        ETERNAL_CORE_API explicit WindowManager(WindowManagerPrivate &windows);
        ~WindowManager() = default;

        WindowManager(const WindowManager &) = delete;
        WindowManager &operator=(const WindowManager &) = delete;
        WindowManager(WindowManager &&) = delete;
        WindowManager &operator=(WindowManager &&) = delete;

        ETERNAL_CORE_API Window &AddWindow(const WindowSettings &settings);
        ETERNAL_CORE_API void RemoveWindow(WindowId id);
    };
}
