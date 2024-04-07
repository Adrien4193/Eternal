#pragma once

#include <memory>
#include <unordered_map>

#include <Eternal/Core/Utils/IdGenerator.h>

#include "Window.h"
#include "WindowSettings.h"

namespace Eternal
{
    class WindowManager
    {
    private:
        WindowHandleFactory m_HandleFactory;
        IdGenerator<WindowId> m_IdGenerator;
        std::unordered_map<WindowId, std::unique_ptr<WindowPrivate>> m_Windows;

    public:
        ETERNAL_CORE_API explicit WindowManager(WindowHandleFactory handleFactory);

        ETERNAL_CORE_API WindowRef Add(const WindowSettings &settings);
        ETERNAL_CORE_API void Remove(WindowRef window);
        ETERNAL_CORE_API void Remove(WindowId id);
        ETERNAL_CORE_API void Poll();
    };
}
