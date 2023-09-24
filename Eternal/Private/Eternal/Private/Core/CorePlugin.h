#pragma once

#include <Eternal/Core/Log.h>
#include <Eternal/Core/Plugin.h>
#include <Eternal/Core/Window.h>

namespace Eternal
{
    class CorePlugin : public Plugin
    {
    private:
        Logger &m_Logger;
        std::unique_ptr<WindowUpdater> m_WindowUpdater;

    public:
        explicit CorePlugin(Logger &logger, std::unique_ptr<WindowUpdater> windowUpdater);

        void Start() override;
        void Stop() override;
        void Update() override;
    };
}
