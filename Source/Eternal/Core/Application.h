#pragma once

#include <functional>
#include <vector>

namespace Eternal
{
    struct ApplicationSettings
    {
        std::function<bool()> IsRunning;
        std::function<void()> Start = [] {};
        std::function<void()> Stop = [] {};
        std::function<void()> Update = [] {};
    };

    class Application
    {
    private:
        ApplicationSettings m_Settings;

    public:
        ETERNAL_CORE_API explicit Application(ApplicationSettings settings);

        ETERNAL_CORE_API void Run();
    };
}
