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
    }

    void Stop()
    {
        m_Logger.Info("Stop");
    }

    void Update()
    {
        m_Logger.Info("Update");

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

    void On(const Eternal::WindowResize &e)
    {
        m_Logger.Info("Window resized: {}x{}", e.Size[0], e.Size[1]);
    }

    void On(const Eternal::WindowClose &)
    {
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

    auto &windowManager = engine.GetWindowManager();
    auto &window = windowManager.AddWindow({
        .Title = "Sandbox",
        .Position = {1600, 900},
        .Size = {400, 400},
    });

    auto sandbox = Sandbox(eventLoop, logger, window);

    application.OnStart([&] { sandbox.Start(); });
    application.OnStop([&] { sandbox.Stop(); });
    application.OnUpdate([&] { sandbox.Update(); });

    application.Run();

    return 0;
}
