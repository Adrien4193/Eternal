#pragma once

#include <memory>
#include <vector>

#include "Engine.h"
#include "Plugin.h"

namespace Eternal
{
    class Application
    {
    private:
        std::unique_ptr<ApplicationLoop> m_Loop;
        std::unique_ptr<Engine> m_Engine;
        std::vector<std::unique_ptr<Plugin>> m_Plugins;

    public:
        explicit Application(std::unique_ptr<ApplicationLoop> loop, std::unique_ptr<Engine> engine);

        Engine &GetEngine() const;
        void AddPlugin(std::unique_ptr<Plugin> plugin);
        void Run();
    };
}
