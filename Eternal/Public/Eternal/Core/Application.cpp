#include "Application.h"

namespace Eternal
{
    Application::Application(std::unique_ptr<ApplicationLoop> loop, std::unique_ptr<Engine> engine):
        m_Loop(std::move(loop)),
        m_Engine(std::move(engine))
    {
    }

    Engine &Application::GetEngine() const
    {
        return *m_Engine;
    }

    void Application::AddPlugin(std::unique_ptr<Plugin> plugin)
    {
        m_Plugins.push_back(std::move(plugin));
    }

    void Application::Run()
    {
        m_Loop->Start();
        for (const auto &plugin : m_Plugins)
        {
            plugin->Start();
        }
        while (m_Loop->IsRunning())
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
