#include "PluginManager.h"

namespace Eternal
{
    void PluginManager::Add(std::unique_ptr<Plugin> plugin)
    {
        m_Plugins.push_back(std::move(plugin));
    }

    void PluginManager::Start()
    {
        for (const auto &plugin : m_Plugins)
        {
            plugin->Start();
        }
    }

    void PluginManager::Stop()
    {
        for (const auto &plugin : m_Plugins)
        {
            plugin->Stop();
        }
    }

    void PluginManager::Update()
    {
        for (const auto &plugin : m_Plugins)
        {
            plugin->Update();
        }
    }
}
