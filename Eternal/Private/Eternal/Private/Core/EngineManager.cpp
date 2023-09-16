#include "EngineManager.h"

namespace Eternal
{
    EngineManager::EngineManager(
        std::unique_ptr<EventLoopManager> eventLoopManager,
        std::unique_ptr<Logger> logger,
        std::unique_ptr<WindowManager> windowManager):
        m_EventLoopManager(std::move(eventLoopManager)),
        m_Logger(std::move(logger)),
        m_WindowManager(std::move(windowManager))
    {
    }

    void EngineManager::AddPlugin(std::unique_ptr<Plugin> plugin)
    {
        m_Plugins.Add(std::move(plugin));
    }

    void EngineManager::Run()
    {
        Start();
        while (m_EventLoopManager->IsRunning())
        {
            Update();
        }
        Stop();
    }

    void EngineManager::Start()
    {
        m_Logger->Info("Starting engine.");
        m_EventLoopManager->Start();
        m_Plugins.Start();
        m_Logger->Info("Engine started.");
    }

    void EngineManager::Stop()
    {
        m_Logger->Info("Stopping engine.");
        m_Plugins.Stop();
        m_Logger->Info("Engine stopped.");
    }

    void EngineManager::Update()
    {
        m_Logger->Trace("Updating engine");
        m_WindowManager->Update();
        if (m_WindowManager->IsClosed())
        {
            m_Logger->Info("Window closed, stopping event loop.");
            m_EventLoopManager->Stop();
            return;
        }
        m_Plugins.Update();
        m_Logger->Trace("Engine updated");
    }
}
