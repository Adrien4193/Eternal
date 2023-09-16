#pragma once

#include <memory>

#include "Engine.h"
#include "Plugin.h"

namespace Eternal
{
    class EngineManager;

    class Application
    {
    private:
        std::unique_ptr<Engine> m_Engine;
        std::unique_ptr<EngineManager> m_EngineManager;

    public:
        explicit Application(std::unique_ptr<Engine> engine, std::unique_ptr<EngineManager> enginePrivate);
        ~Application();

        Engine &GetEngine() const;
        void AddPlugin(std::unique_ptr<Plugin> plugin);
        void Run();
    };
}
