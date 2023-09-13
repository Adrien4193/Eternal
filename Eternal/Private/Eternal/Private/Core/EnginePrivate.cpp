#include "EnginePrivate.h"

namespace Eternal
{
    EnginePrivate::EnginePrivate(
        std::unique_ptr<EventLoop> eventLoop,
        std::unique_ptr<EventLoopPrivate> eventLoopPrivate,
        std::unique_ptr<Logger> logger,
        std::unique_ptr<WindowClass> windowClass,
        std::unique_ptr<Window> window,
        std::unique_ptr<WindowPrivate> windowPrivate):
        m_EventLoop(std::move(eventLoop)),
        m_EventLoopPrivate(std::move(eventLoopPrivate)),
        m_Logger(std::move(logger)),
        m_WindowClass(std::move(windowClass)),
        m_Window(std::move(window)),
        m_WindowPrivate(std::move(windowPrivate))
    {
    }

    void EnginePrivate::AddPlugin(std::unique_ptr<Plugin> plugin)
    {
        m_Plugins.Add(std::move(plugin));
    }

    void EnginePrivate::Run()
    {
        Start();
        while (m_EventLoopPrivate->IsRunning())
        {
            Update();
        }
        Stop();
    }

    void EnginePrivate::Start()
    {
        m_Logger->Info("Starting engine.");
        m_EventLoopPrivate->Start();
        m_Plugins.Start();
        m_Logger->Info("Engine started.");
    }

    void EnginePrivate::Stop()
    {
        m_Logger->Info("Stopping engine.");
        m_Plugins.Stop();
        m_Logger->Info("Engine stopped.");
    }

    void EnginePrivate::Update()
    {
        m_Logger->Trace("Updating engine");
        m_WindowPrivate->Poll();
        if (m_WindowPrivate->IsClosed())
        {
            m_Logger->Info("Window closed, stopping event loop.");
            m_EventLoop->Stop();
            return;
        }
        m_Plugins.Update();
        m_Logger->Trace("Engine updated");
    }
}
