#pragma once

namespace Eternal
{
    class Plugin
    {
    public:
        virtual ~Plugin() = default;

        virtual void Start()
        {
        }

        virtual void Stop()
        {
        }

        virtual void Update()
        {
        }
    };
}
