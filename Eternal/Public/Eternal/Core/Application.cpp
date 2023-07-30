#include "Application.h"

namespace
{
    using namespace Eternal;

    class ApplicationLoop : public EventLoop
    {
    private:
        PluginManager &m_PluginManager;

    public:
        explicit ApplicationLoop(PluginManager &pluginManager):
            m_PluginManager(pluginManager)
        {
        }

        virtual void Stop() override
        {
            m_PluginManager.Stop();
        }
    };
}

namespace Eternal
{
    void PluginManager::Add(std::unique_ptr<Plugin> plugin)
    {
        m_Plugins.push_back(std::move(plugin));
    }

    void PluginManager::Stop()
    {
        m_Running = false;
    }

    void PluginManager::Run()
    {
        m_Running = true;
        for (const auto &plugin : m_Plugins)
        {
            plugin->Start();
        }
        while (m_Running)
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

    Application::Application(std::unique_ptr<Engine> engine, std::unique_ptr<PluginManager> pluginManager):
        m_Engine(std::move(engine)),
        m_PluginManager(std::move(pluginManager))
    {
    }

    Application::~Application()
    {
    }

    Engine &Application::GetEngine() const
    {
        return *m_Engine;
    }

    void Application::AddPlugin(std::unique_ptr<Plugin> plugin)
    {
        m_PluginManager->Add(std::move(plugin));
    }

    void Application::Run()
    {
        m_PluginManager->Run();
    }

    std::unique_ptr<Application> CreateApplication(std::string name)
    {
        auto pluginManager = std::make_unique<PluginManager>();
        auto eventLoop = std::make_unique<ApplicationLoop>(*pluginManager);
        auto logger = CreateConsoleLogger(std::move(name));
        auto engine = std::make_unique<Engine>(std::move(eventLoop), std::move(logger));
        return std::make_unique<Application>(std::move(engine), std::move(pluginManager));
    }
}
