#pragma once

#include <memory>

#include <Eternal/Core/Application.h>

#include "EnginePrivate.h"

namespace Eternal
{
    class ApplicationPrivate : public Application
    {
    private:
        std::unique_ptr<EnginePrivate> m_Engine;
        std::unique_ptr<Engine> m_Interface;

    public:
        explicit ApplicationPrivate(std::unique_ptr<EnginePrivate> engine, std::unique_ptr<Engine> interface);

        Engine &GetEngine() const override;
        void AddPlugin(std::unique_ptr<Plugin> plugin) override;
        void Run() override;
    };
}
