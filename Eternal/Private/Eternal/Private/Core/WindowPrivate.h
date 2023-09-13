#pragma once

#include <memory>
#include <string>

#include <Eternal/Core/Window.h>

namespace Eternal
{
    class WindowPrivate
    {
    private:
        std::unique_ptr<WindowHandle> m_Handle;
        std::unique_ptr<WindowProperties> m_Properties;

    public:
        explicit WindowPrivate(std::unique_ptr<WindowHandle> handle, std::unique_ptr<WindowProperties> properties);

        bool IsClosed() const;
        void Poll();
    };
}
