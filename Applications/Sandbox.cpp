#include <Eternal/Core/Factory.h>
#include <Eternal/Core/Logging/ConsoleLogger.h>
#include <Eternal/Platform/NativeWindow.h>

class Sandbox
{
private:
    Eternal::EventLoop &m_EventLoop;
    Eternal::Logger &m_Logger;
    Eternal::Window &m_Window;

public:
    explicit Sandbox(Eternal::EventLoop &eventLoop, Eternal::Logger &logger, Eternal::Window &window):
        m_EventLoop(eventLoop),
        m_Logger(logger),
        m_Window(window)
    {
    }

    ~Sandbox() = default;

    Sandbox(const Sandbox &) = delete;
    Sandbox &operator=(const Sandbox &) = delete;
    Sandbox(Sandbox &&) = delete;
    Sandbox &operator=(Sandbox &&) = delete;

    void Start()
    {
        m_Logger.Info("Start");

        m_Window.SetTitle("Test");
        m_Window.SetPosition({100, 1000});
        m_Window.Resize({200, 200});
    }

    void Stop()
    {
        m_Logger.Info("Stop");
    }

    void Update()
    {
        m_Logger.Debug("Update");

        for (const auto &e : m_Window.GetEvents())
        {
            std::visit([this](const auto &e) { On(e); }, e);
        }
    }

private:
    void On(const Eternal::WindowMove &e)
    {
        m_Logger.Info("Window moved: [{}, {}]", e.Position[0], e.Position[1]);
    }

    void On(const Eternal::WindowRename &e)
    {
        m_Logger.Info("Window renamed: {}", e.Title);
    }

    void On(const Eternal::WindowResize &e)
    {
        m_Logger.Info("Window resized: {}x{}", e.Size[0], e.Size[1]);
    }

    void On(const Eternal::WindowClose &e)
    {
        (void)e;
        m_EventLoop.Stop();
    }

    void On(const auto &e)
    {
        (void)e;
    }
};

int main()
{
    auto application = Eternal::CreateApplication({
        .Logger = Eternal::CreateConsoleLogger("Engine"),
        .WindowHandleFactory = Eternal::CreateNativeWindowHandleFactory(),
    });

    auto &engine = application.GetEngine();

    auto &eventLoop = engine.GetEventLoop();

    auto logger = Eternal::CreateConsoleLogger("Sandbox");
    logger.SetLevel(Eternal::LogLevel::Info);

    auto &windowManager = engine.GetWindowManager();
    auto &window = windowManager.AddWindow({
        .Title = "Sandbox",
        .Position = {1200, 400},
        .Size = {800, 800},
    });

    auto sandbox = Sandbox(eventLoop, logger, window);

    application.OnStart([&] { sandbox.Start(); });
    application.OnStop([&] { sandbox.Stop(); });
    application.OnUpdate([&] { sandbox.Update(); });

    application.Run();

    return 0;
}
