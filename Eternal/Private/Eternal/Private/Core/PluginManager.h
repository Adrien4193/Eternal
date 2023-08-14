#pragma once

#include <memory>
#include <vector>

#include <Eternal/Core/Plugin.h>

namespace Eternal
{
    class PluginManager
    {
    private:
        std::vector<std::unique_ptr<Plugin>> m_Plugins;

    public:
        void Add(std::unique_ptr<Plugin> plugin);
        void Start();
        void Stop();
        void Update();
    };
}
