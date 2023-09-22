#pragma once

namespace Eternal
{
    class ApplicationLoop
    {
    private:
        bool m_Running = false;

    public:
        bool IsRunning() const;
        void Start();
        void Stop();
    };

    class EventLoop
    {
    private:
        ApplicationLoop &m_Loop;

    public:
        explicit EventLoop(ApplicationLoop &loop);

        void Stop();
    };
}
