#pragma once

#include <map>

#include <Eternal/Core/Utils/IdGenerator.h>

#include "Window.h"

namespace Eternal
{
    class WindowManager
    {
    private:
        WindowFactory m_Factory;
        IdGenerator<WindowId> m_IdGenerator;
        std::map<WindowId, WindowPrivate> m_Windows;

    public:
        ETERNAL_CORE_API explicit WindowManager(WindowFactory handleFactory);

        ETERNAL_CORE_API Window Add(const WindowSettings &settings);
        ETERNAL_CORE_API void Remove(Window window);
        ETERNAL_CORE_API void Remove(WindowId id);
        ETERNAL_CORE_API void Poll();
    };
}
