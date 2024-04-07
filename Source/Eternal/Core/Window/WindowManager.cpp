#include "WindowManager.h"

#include <cassert>
#include <format>
#include <stdexcept>

namespace Eternal
{
    WindowManager::WindowManager(WindowHandleFactory handleFactory):
        m_HandleFactory(std::move(handleFactory))
    {
    }

    WindowRef WindowManager::Add(const WindowSettings &settings)
    {
        auto handle = m_HandleFactory(settings);
        auto id = m_IdGenerator.Next();
        try
        {
            auto window = CreateWindowPrivate(id, std::move(handle), settings);
            auto [i, inserted] = m_Windows.emplace(id, std::move(window));
            assert(inserted);
            return WindowRef(i->second);
        }
        catch (...)
        {
            m_IdGenerator.Recycle(id);
            throw;
        }
    }

    void WindowManager::Remove(WindowRef window)
    {
        Remove(window.GetId());
    }

    void WindowManager::Remove(WindowId id)
    {
        auto i = m_Windows.find(id);
        if (i == m_Windows.end())
        {
            throw std::invalid_argument(std::format("Invalid window ID: {}", id));
        }
        m_Windows.erase(i);
        m_IdGenerator.Recycle(id);
    }

    void WindowManager::Poll()
    {
        for (auto &[id, window] : m_Windows)
        {
            PollWindowPrivate(window);
        }
    }
}
