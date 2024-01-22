#pragma once

#include <functional>
#include <memory>

#include <Eternal/Core/Engine/Engine.h>

namespace Eternal
{
    class Application
    {
    private:
        std::function<bool()> m_IsRunning;
        std::unique_ptr<Engine> m_Engine;
        std::vector<std::function<void()>> m_StartHandlers;
        std::vector<std::function<void()>> m_UpdateHandlers;
        std::vector<std::function<void()>> m_StopHandlers;

    public:
        ETERNAL_EXPORT explicit Application(std::function<bool()> isRunning, std::unique_ptr<Engine> engine);
        ~Application() = default;

        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;
        Application(Application &&) = delete;
        Application &operator=(Application &&) = delete;

        ETERNAL_EXPORT Engine &GetEngine();
        ETERNAL_EXPORT void OnStart(std::function<void()> handler);
        ETERNAL_EXPORT void OnStop(std::function<void()> handler);
        ETERNAL_EXPORT void OnUpdate(std::function<void()> handler);
        ETERNAL_EXPORT void Run();
    };
}
