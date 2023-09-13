#include "Application.h"

#include <Eternal/Private/Core/EnginePrivate.h>

namespace Eternal
{
    Application::Application(std::unique_ptr<Engine> engine, std::unique_ptr<EnginePrivate> enginePrivate):
        m_Engine(std::move(engine)),
        m_EnginePrivate(std::move(enginePrivate))
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
        m_EnginePrivate->AddPlugin(std::move(plugin));
    }

    void Application::Run()
    {
        m_EnginePrivate->Run();
    }
}
