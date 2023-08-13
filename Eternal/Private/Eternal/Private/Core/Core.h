#pragma once

#include <Eternal/Core/Plugin.h>

#include "WindowMonitor.h"

namespace Eternal
{
    class Core : public Plugin
    {
    private:
        WindowMonitor &m_WindowMonitor;

    public:
        explicit Core(WindowMonitor &windowMonitor);

        virtual void Start() override;
        virtual void Update() override;
    };
}
