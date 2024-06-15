#pragma once

#include <map>

#include <Eternal/Core/Utils/IdGenerator.h>

#include "Window.h"

namespace Eternal
{
    class WindowManager
    {
    private:
        WindowHandleFactory m_HandleFactory;
        IdGenerator<WindowId> m_IdGenerator;
        std::map<WindowId, WindowPrivate> m_Windows;

    public:
        ETERNAL_CORE_API explicit WindowManager(WindowHandleFactory handleFactory);

        ETERNAL_CORE_API WindowRef Add(const WindowSettings &settings);
        ETERNAL_CORE_API void Remove(WindowRef window);
        ETERNAL_CORE_API void Remove(WindowId id);
        ETERNAL_CORE_API void Poll();
    };
}
