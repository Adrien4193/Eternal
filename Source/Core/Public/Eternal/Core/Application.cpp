#include "Application.h"

namespace Eternal
{
    Application::Application(std::function<bool()> isRunning, std::unique_ptr<Engine> engine):
        m_IsRunning(std::move(isRunning)),
        m_Engine(std::move(engine))
    {
    }

    Engine &Application::GetEngine()
    {
        return *m_Engine;
    }

    void Application::OnStart(std::function<void()> handler)
    {
        m_StartHandlers.push_back(std::move(handler));
    }

    void Application::OnStop(std::function<void()> handler)
    {
        m_StopHandlers.push_back(std::move(handler));
    }

    void Application::OnUpdate(std::function<void()> handler)
    {
        m_UpdateHandlers.push_back(std::move(handler));
    }

    void Application::Run()
    {
        for (const auto &handler : m_StartHandlers)
        {
            handler();
        }
        while (m_IsRunning())
        {
            for (const auto &handler : m_UpdateHandlers)
            {
                handler();
            }
        }
        for (const auto &handler : m_StopHandlers)
        {
            handler();
        }
    }
}
