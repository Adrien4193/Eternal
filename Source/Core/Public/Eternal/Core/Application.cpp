#include "Application.h"

namespace Eternal
{
    void ApplicationScheduler::OnStart(std::function<void()> handler)
    {
        m_StartHandlers.push_back(std::move(handler));
    }

    void ApplicationScheduler::Start()
    {
        for (const auto &handler : m_StartHandlers)
        {
            handler();
        }
    }

    void ApplicationScheduler::OnStop(std::function<void()> handler)
    {
        m_StopHandlers.push_back(std::move(handler));
    }

    void ApplicationScheduler::Stop()
    {
        for (const auto &handler : m_StopHandlers)
        {
            handler();
        }
    }

    void ApplicationScheduler::OnUpdate(std::function<void()> handler)
    {
        m_UpdateHandlers.push_back(std::move(handler));
    }

    void ApplicationScheduler::Update()
    {
        for (const auto &handler : m_UpdateHandlers)
        {
            handler();
        }
    }

    Application::Application(std::unique_ptr<EnginePrivate> enginePrivate, std::unique_ptr<Engine> engine, ApplicationScheduler scheduler):
        m_EnginePrivate(std::move(enginePrivate)),
        m_Engine(std::move(engine)),
        m_Scheduler(std::move(scheduler))
    {
    }

    Engine &Application::GetEngine() const
    {
        return *m_Engine;
    }

    void Application::OnStart(std::function<void()> handler)
    {
        m_Scheduler.OnStart(std::move(handler));
    }

    void Application::OnStop(std::function<void()> handler)
    {
        m_Scheduler.OnStop(std::move(handler));
    }

    void Application::OnUpdate(std::function<void()> handler)
    {
        m_Scheduler.OnUpdate(std::move(handler));
    }

    void Application::Run()
    {
        m_Scheduler.Start();
        while (m_EnginePrivate->EventLoopPrivate->Running)
        {
            m_Scheduler.Update();
        }
        m_Scheduler.Stop();
    }
}
