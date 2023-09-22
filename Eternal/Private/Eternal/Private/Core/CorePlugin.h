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
        WindowRegistry &m_Windows;

    public:
        explicit CorePlugin(Logger &logger, WindowRegistry &windows);

        void Start() override;
        void Stop() override;
        void Update() override;
    };
}
