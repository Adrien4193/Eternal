#include "Application.h"

namespace Eternal
{
    void Application::OnStart(std::function<void()> handler)
    {
        m_StopHandlers.push_back(std::move(handler));
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
        m_Running = true;
        for (const auto &handler : m_StartHandlers)
        {
            handler();
        }
        while (m_Running)
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

    void Application::Quit()
    {
        m_Running = false;
    }
}
