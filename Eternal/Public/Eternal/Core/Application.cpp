#include "Application.h"

#include <Eternal/Private/Core/EngineManager.h>

namespace Eternal
{
    Application::Application(std::unique_ptr<Engine> engine, std::unique_ptr<EngineManager> enginePrivate):
        m_Engine(std::move(engine)),
        m_EngineManager(std::move(enginePrivate))
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
        m_EngineManager->AddPlugin(std::move(plugin));
    }

    void Application::Run()
    {
        m_EngineManager->Run();
    }
}