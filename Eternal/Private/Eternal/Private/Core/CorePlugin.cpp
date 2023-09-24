#include "CorePlugin.h"

namespace Eternal
{
    CorePlugin::CorePlugin(Logger &logger, std::unique_ptr<WindowUpdater> windowUpdater):
        m_Logger(logger),
        m_WindowUpdater(std::move(windowUpdater))
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
        m_WindowUpdater->PollWindows();
        m_Logger.Trace("Engine updated.");
    }
}
