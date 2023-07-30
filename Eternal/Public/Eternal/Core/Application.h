#pragma once

#include <memory>
#include <vector>

#include "Engine.h"
#include "Plugin.h"

namespace Eternal
{
    class PluginManager
    {
    private:
        std::vector<std::unique_ptr<Plugin>> m_Plugins;
        bool m_Running = false;

    public:
        void Add(std::unique_ptr<Plugin> plugin);
        void Stop();
        void Run();
    };

    class Application
    {
    private:
        std::unique_ptr<Engine> m_Engine;
        std::unique_ptr<PluginManager> m_PluginManager;

    public:
        explicit Application(std::unique_ptr<Engine> engine, std::unique_ptr<PluginManager> pluginManager);
        ~Application();

        Engine &GetEngine() const;
        void AddPlugin(std::unique_ptr<Plugin> plugin);
        void Run();
    };

    std::unique_ptr<Application> CreateApplication(std::string name);
}
