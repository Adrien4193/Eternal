#include <Eternal/Eternal.h>

class SandboxPlugin : public Eternal::Plugin
{
private:
    Eternal::Logger &m_Logger;

public:
    explicit SandboxPlugin(Eternal::Logger &logger):
        m_Logger(logger)
    {
    }

    virtual void Update() override
    {
        m_Logger.Info("Test: {}", 1);
    }
};

int main()
{
    auto application = Eternal::CreateApplication("Sandbox");
    auto &engine = application->GetEngine();
    auto &logger = engine.GetLogger();
    auto plugin = std::make_unique<SandboxPlugin>(logger);
    application->AddPlugin(std::move(plugin));
    application->Run();
}
