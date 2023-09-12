#include "ApplicationPrivate.h"

namespace Eternal
{
    ApplicationPrivate::ApplicationPrivate(std::unique_ptr<EnginePrivate> engine, std::unique_ptr<Engine> interface):
        m_Engine(std::move(engine)),
        m_Interface(std::move(interface))
    {
    }

    Engine &ApplicationPrivate::GetEngine() const
    {
        return *m_Interface;
    }

    void ApplicationPrivate::AddPlugin(std::unique_ptr<Plugin> plugin)
    {
        m_Engine->AddPlugin(std::move(plugin));
    }

    void ApplicationPrivate::Run()
    {
        m_Engine->Start();
        while (m_Engine->IsRunning())
        {
            m_Engine->Update();
        }
        m_Engine->Stop();
    }
}
