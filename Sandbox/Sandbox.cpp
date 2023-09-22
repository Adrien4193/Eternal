#include <Eternal/Eternal.h>

class SandboxPlugin : public Eternal::Plugin
{
private:
    Eternal::EventLoop &m_EventLoop;
    Eternal::Logger &m_Logger;
    Eternal::Window &m_Window;

public:
    explicit SandboxPlugin(Eternal::EventLoop &eventLoop, Eternal::Logger &logger, Eternal::Window &window):
        m_EventLoop(eventLoop),
        m_Logger(logger),
        m_Window(window)
    {
    }

    void Update() override
    {
        m_Logger.Info("Test: {}", 1);
        if (m_Window.IsClosed())
        {
            m_Logger.Info("Window closed.");
            m_EventLoop.Stop();
        }
    }
};

int main()
{
    auto application = Eternal::CreateApplication("Sandbox");

    auto &engine = application->GetEngine();

    auto &eventLoop = engine.GetEventLoop();
    auto &logger = engine.GetLogger();
    auto &windowManager = engine.GetWindowManager();

    auto settings = Eternal::WindowSettings();
    settings.Title = "Test";
    settings.Size = {400.0f, 400.0f};
    auto &window = windowManager.AddWindow(settings);

    auto plugin = std::make_unique<SandboxPlugin>(eventLoop, logger, window);
    application->AddPlugin(std::move(plugin));

    application->Run();
}
