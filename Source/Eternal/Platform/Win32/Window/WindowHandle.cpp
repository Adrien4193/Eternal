#include "WindowHandle.h"

#include <cassert>
#include <utility>

#include "Utils.h"

namespace Eternal
{
    void EventBuffer::Add(WindowEvent e)
    {
        auto lock = std::lock_guard(m_Mutex);
        m_Events.push_back(std::move(e));
    }

    std::vector<WindowEvent> EventBuffer::Poll()
    {
        auto lock = std::lock_guard(m_Mutex);
        return std::exchange(m_Events, {});
    }

    NativeWindowHandle::Deleter::Deleter(GuiThread &guiThread):
        m_GuiThread(&guiThread)
    {
    }

    void NativeWindowHandle::Deleter::operator()(HWND handle) const
    {
        auto destroyWindow = [=] { return DestroyWindow(handle); };
        auto success = m_GuiThread->Run(destroyWindow);
        assert(success == TRUE);
    }

    NativeWindowHandle::NativeWindowHandle(GuiThread &guiThread, HWND handle, std::unique_ptr<EventBuffer> events):
        m_Handle(handle, Deleter(guiThread)),
        m_Events(std::move(events))
    {
    }

    HWND NativeWindowHandle::Get() const
    {
        return m_Handle.get();
    }

    std::vector<WindowEvent> NativeWindowHandle::Poll()
    {
        return m_Events->Poll();
    }

    void NativeWindowHandle::Show(int code)
    {
        ShowWindow(m_Handle.get(), code);
    }

    void NativeWindowHandle::SetTitle(std::string_view title)
    {
        auto wtitle = ToUtf16(title);
        auto success = SetWindowTextW(m_Handle.get(), wtitle.c_str());
        if (success == FALSE)
        {
            throw LastErrorToException("Failed to set window title");
        }
    }

    void NativeWindowHandle::SetPosition(Vector2 position)
    {
        auto flags = SWP_NOSIZE | SWP_NOACTIVATE;
        auto width = static_cast<int>(position[0]);
        auto height = static_cast<int>(position[1]);
        auto success = SetWindowPos(m_Handle.get(), nullptr, width, height, 0, 0, flags);
        if (success == FALSE)
        {
            throw LastErrorToException("Failed to set window position");
        }
    }

    void NativeWindowHandle::Resize(Vector2 size)
    {
        auto flags = SWP_NOMOVE | SWP_NOACTIVATE;
        auto width = static_cast<int>(size[0]);
        auto height = static_cast<int>(size[1]);
        auto success = SetWindowPos(m_Handle.get(), nullptr, 0, 0, width, height, flags);
        if (success == FALSE)
        {
            throw LastErrorToException("Failed to set window size");
        }
    }
}
