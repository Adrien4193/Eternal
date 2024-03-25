#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <Eternal/Core/Engine/Engine.h>

namespace Eternal
{
    class ApplicationScheduler
    {
    private:
        std::vector<std::function<void()>> m_StartHandlers;
        std::vector<std::function<void()>> m_UpdateHandlers;
        std::vector<std::function<void()>> m_StopHandlers;

    public:
        void OnStart(std::function<void()> handler);
        void Start();
        void OnStop(std::function<void()> handler);
        void Stop();
        void OnUpdate(std::function<void()> handler);
        void Update();
    };

    class Application
    {
    private:
        std::unique_ptr<EnginePrivate> m_EnginePrivate;
        std::unique_ptr<Engine> m_Engine;
        ApplicationScheduler m_Scheduler;

    public:
        ETERNAL_CORE_API explicit Application(
            std::unique_ptr<EnginePrivate> enginePrivate,
            std::unique_ptr<Engine> engine,
            ApplicationScheduler scheduler);

        ETERNAL_CORE_API Engine &GetEngine() const;
        ETERNAL_CORE_API void OnStart(std::function<void()> handler);
        ETERNAL_CORE_API void OnStop(std::function<void()> handler);
        ETERNAL_CORE_API void OnUpdate(std::function<void()> handler);
        ETERNAL_CORE_API void Run();
    };
}
