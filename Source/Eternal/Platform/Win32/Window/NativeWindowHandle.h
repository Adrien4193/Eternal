#pragma once

#include <memory>
#include <mutex>
#include <string_view>
#include <vector>

#include <Windows.h>

#include <Eternal/Core/Math/Types.h>
#include <Eternal/Core/Window/WindowEvents.h>

#include "GuiThread.h"

namespace Eternal
{
    class EventBuffer
    {
    private:
        std::mutex m_Mutex;
        std::vector<WindowEvent> m_Events;

    public:
        void Add(WindowEvent e);
        std::vector<WindowEvent> Poll();
    };

    class NativeWindowHandle
    {
    private:
        class Deleter
        {
        private:
            GuiThread *m_GuiThread;

        public:
            explicit Deleter(GuiThread &guiThread);

            void operator()(HWND handle) const;
        };

        std::unique_ptr<HWND__, Deleter> m_Handle;
        std::unique_ptr<EventBuffer> m_Events;

    public:
        explicit NativeWindowHandle(GuiThread &guiThread, HWND handle, std::unique_ptr<EventBuffer> events);

        HWND Get() const;
        std::vector<WindowEvent> Poll();
        void Show(int code);
        void SetTitle(std::string_view title);
        void SetPosition(Vector2 position);
        void Resize(Vector2 size);
    };
}
