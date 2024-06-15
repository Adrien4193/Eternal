#include "Application.h"

namespace Eternal
{
    Application::Application(ApplicationSettings settings):
        m_Settings(std::move(settings))
    {
    }

    void Application::Run()
    {
        m_Settings.Start();

        while (m_Settings.IsRunning())
        {
            m_Settings.Update();
        }

        m_Settings.Stop();
    }
}
