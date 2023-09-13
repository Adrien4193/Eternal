#pragma once

#include <memory>

#include "Engine.h"
#include "Plugin.h"

namespace Eternal
{
    class EnginePrivate;

    class Application
    {
    private:
        std::unique_ptr<Engine> m_Engine;
        std::unique_ptr<EnginePrivate> m_EnginePrivate;

    public:
        explicit Application(std::unique_ptr<Engine> engine, std::unique_ptr<EnginePrivate> enginePrivate);
        ~Application();

        Engine &GetEngine() const;
        void AddPlugin(std::unique_ptr<Plugin> plugin);
        void Run();
    };
}
