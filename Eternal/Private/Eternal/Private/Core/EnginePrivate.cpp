#include "EnginePrivate.h"

namespace Eternal
{
    EnginePrivate::EnginePrivate(std::unique_ptr<EventLoopPrivate> eventLoop, std::unique_ptr<Logger> logger, std::unique_ptr<WindowPrivate> window):
        m_EventLoop(std::move(eventLoop)),
        m_Logger(std::move(logger)),
        m_Window(std::move(window))
    {
    }

    auto EnginePrivate::IsRunning() const -> bool
    {
        return m_EventLoop->IsRunning();
    }

    void EnginePrivate::AddPlugin(std::unique_ptr<Plugin> plugin)
    {
        m_Plugins.Add(std::move(plugin));
    }

    void EnginePrivate::Start()
    {
        m_EventLoop->Start();
        m_Plugins.Start();
    }

    void EnginePrivate::Stop()
    {
        m_Plugins.Stop();
    }

    void EnginePrivate::Update()
    {
        m_Plugins.Update();
        m_Window->Poll();
        if (m_Window->IsClosed())
        {
            m_EventLoop->Stop();
        }
    }

    EngineAdapter::EngineAdapter(std::unique_ptr<EventLoop> eventLoop, Logger &logger, std::unique_ptr<Window> window):
        m_EventLoop(std::move(eventLoop)),
        m_Logger(logger),
        m_Window(std::move(window))
    {
    }

    auto EngineAdapter::GetEventLoop() const -> EventLoop &
    {
        return *m_EventLoop;
    }

    auto EngineAdapter::GetLogger() const -> Logger &
    {
        return m_Logger;
    }

    auto EngineAdapter::GetWindow() const -> Window &
    {
        return *m_Window;
    }
}
