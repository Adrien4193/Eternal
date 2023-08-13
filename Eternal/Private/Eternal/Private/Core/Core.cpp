#include "Core.h"

namespace Eternal
{
    Core::Core(WindowMonitor &windowMonitor):
        m_WindowMonitor(windowMonitor)
    {
    }

    void Core::Start()
    {
        m_WindowMonitor.ShowWindow();
    }

    void Core::Update()
    {
        m_WindowMonitor.Update();
    }
}
