#include "CorePlugin.h"

namespace Eternal
{
    CorePlugin::CorePlugin(Logger &logger, WindowRegistry &windows):
        m_Logger(logger),
        m_Windows(windows)
    {
    }

    void CorePlugin::Start()
    {
        m_Logger.Info("Engine started.");
    }

    void CorePlugin::Stop()
    {
        m_Logger.Info("Engine stopped.");
    }

    void CorePlugin::Update()
    {
        m_Logger.Trace("Updating engine.");
        m_Windows.Update();
        m_Logger.Trace("Engine updated.");
    }
}
