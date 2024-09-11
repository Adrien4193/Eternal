#include <thread>

#include <Eternal/Core/Application.h>
#include <Eternal/Core/Logging/ConsoleLogger.h>
#include <Eternal/Core/Window/WindowManager.h>
#include <Eternal/Platform/Platform.h>

class Sandbox
{
private:
    Eternal::Logger *m_Logger;
    Eternal::Window m_Window;
    bool m_Running = false;

public:
    explicit Sandbox(Eternal::Logger &logger, Eternal::Window window):
        m_Logger(&logger),
        m_Window(window)
    {
    }

    bool IsRunning() const
    {
        return m_Running;
    }

    void Start()
    {
        m_Logger->Info("Start");

        m_Window.SetTitle("Test");
        m_Window.SetPosition({100, 1000});
        m_Window.Resize({200, 200});

        m_Running = true;
    }

    void Stop()
    {
        m_Logger->Info("Stop");
    }

    void Update()
    {
        m_Logger->Debug("Update");

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        m_Window.On([this](const auto &e) { On(e); });
    }

private:
    void On(const Eternal::WindowError &e)
    {
        std::rethrow_exception(e.exception);
    }

    void On(const Eternal::WindowMove &e)
    {
        m_Logger->Info("Window moved: [{}, {}]", e.Position[0], e.Position[1]);
    }

    void On(const Eternal::WindowRename &e)
    {
        m_Logger->Info("Window renamed: {}", e.Title);
    }

    void On(const Eternal::WindowResize &e)
    {
        m_Logger->Info("Window resized: {}x{}", e.Size[0], e.Size[1]);
    }

    void On(const Eternal::WindowClose &)
    {
        m_Logger->Info("Window closed");
        m_Running = false;
    }

    void On(const Eternal::WindowInput &)
    {
        m_Logger->Info("Window input");
    }
};

int main()
{
    auto windows = Eternal::CreateWindowManager();

    auto logger = Eternal::CreateConsoleLogger("Sandbox");
    logger.SetLevel(Eternal::LogLevel::Info);

    auto window = windows.Add({
        .Title = "Sandbox",
        .Position = {1200, 400},
        .Size = {800, 800},
    });

    window.Show();

    auto sandbox = Sandbox(logger, window);

    auto update = [&]
    {
        windows.Poll();
        sandbox.Update();
    };

    auto application = Eternal::Application({
        .IsRunning = [&] { return sandbox.IsRunning(); },
        .Start = [&] { sandbox.Start(); },
        .Stop = [&] { sandbox.Stop(); },
        .Update = update,
    });

    application.Run();

    return 0;
}
