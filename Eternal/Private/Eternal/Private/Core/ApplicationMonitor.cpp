#include "ApplicationMonitor.h"

namespace Eternal
{
    ApplicationMonitor::ApplicationMonitor(std::unique_ptr<EngineMonitor> monitor, std::vector<std::unique_ptr<Plugin>> plugins):
        m_Monitor(std::move(monitor)),
        m_Plugins(std::move(plugins))
    {
    }

    Engine &ApplicationMonitor::GetEngine() const
    {
        return m_Monitor->GetEngine();
    }

    void ApplicationMonitor::AddPlugin(std::unique_ptr<Plugin> plugin)
    {
        m_Plugins.push_back(std::move(plugin));
    }

    void ApplicationMonitor::Run()
    {
        m_Monitor->Start();
        for (const auto &plugin : m_Plugins)
        {
            plugin->Start();
        }
        while (m_Monitor->IsRunning())
        {
            for (const auto &plugin : m_Plugins)
            {
                plugin->Update();
            }
        }
        for (const auto &plugin : m_Plugins)
        {
            plugin->Stop();
        }
    }
}
