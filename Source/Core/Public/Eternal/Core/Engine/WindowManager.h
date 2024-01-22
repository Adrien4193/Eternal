#pragma once

#include <functional>
#include <string_view>

#include <Eternal/Core/Math/Types.h>
#include <Eternal/Core/Utils/EventQueue.h>
#include <Eternal/Core/Utils/IdGenerator.h>

#include "Window.h"

namespace Eternal
{
    struct WindowSettings
    {
        std::string_view Title;
        Vector2 Position = {};
        Vector2 Size = {};
    };

    using WindowListener = std::function<void(std::any)>;

    struct WindowHandleSettings
    {
        WindowSettings Settings;
        WindowListener Listener;
    };

    struct GuiThread
    {
        std::function<WindowHandle(const WindowHandleSettings &)> CreateWindowHandle;
        std::function<void(const WindowHandle &)> DestroyWindowHandle;
    };

    class WindowManager
    {
    private:
        GuiThread m_GuiThread;
        IdGenerator<WindowId> m_IdGenerator;

    public:
        ETERNAL_EXPORT explicit WindowManager(GuiThread guiThread);

        ETERNAL_EXPORT Window &AddWindow(const WindowSettings &settings);
        ETERNAL_EXPORT void RemoveWindow(WindowId id);
    };
}
