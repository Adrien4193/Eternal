#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace Eternal
{
    class Application
    {
    private:
        bool m_Running = false;
        std::vector<std::function<void()>> m_StartHandlers;
        std::vector<std::function<void()>> m_StopHandlers;
        std::vector<std::function<void()>> m_UpdateHandlers;

    public:
        ETERNAL_CORE_API void OnStart(std::function<void()> handler);
        ETERNAL_CORE_API void OnStop(std::function<void()> handler);
        ETERNAL_CORE_API void OnUpdate(std::function<void()> handler);
        ETERNAL_CORE_API void Run();
        ETERNAL_CORE_API void Quit();
    };
}
