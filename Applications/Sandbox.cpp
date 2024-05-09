#include <Eternal/Core/Application.h>
#include <Eternal/Core/Logging/ConsoleLogger.h>
#include <Eternal/Core/Window/WindowManager.h>
#include <Eternal/Platform/Platform.h>

class Sandbox : public Eternal::Application
{
private:
    Eternal::Logger *m_Logger;
    Eternal::WindowRef m_Window;

public:
    explicit Sandbox(Eternal::Logger &logger, Eternal::WindowRef window):
        m_Logger(&logger),
        m_Window(window)
    {
    }

    void Start()
    {
        m_Logger->Info("Start");

        m_Window.SetTitle("Test");
        m_Window.SetPosition({100, 1000});
        m_Window.Resize({200, 200});
    }

    void Stop()
    {
        m_Logger->Info("Stop");
    }

    void Update()
    {
        m_Logger->Debug("Update");

        for (const auto &e : m_Window.GetEvents())
        {
            std::visit([this](const auto &e) { On(e); }, e);
        }
    }

private:
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
        Quit();
    }

    void On(const auto &)
    {
    }
};

int main()
{
    auto nativeWindowHandleFactory = Eternal::CreateNativeWindowHandleFactory();
    auto windows = Eternal::WindowManager(nativeWindowHandleFactory);

    auto logger = Eternal::CreateConsoleLogger("Sandbox");
    logger.SetLevel(Eternal::LogLevel::Debug);

    auto window = windows.Add({
        .Title = "Sandbox",
        .Position = {1200, 400},
        .Size = {800, 800},
    });

    window.Show();

    auto sandbox = Sandbox(logger, window);

    sandbox.OnStart([&] { sandbox.Start(); });
    sandbox.OnStop([&] { sandbox.Stop(); });
    sandbox.OnUpdate([&] { windows.Poll(); });
    sandbox.OnUpdate([&] { sandbox.Update(); });

    sandbox.Run();

    return 0;
}
