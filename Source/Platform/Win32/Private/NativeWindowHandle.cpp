#include "NativeWindowHandle.h"

#include <cassert>

#include "Utils.h"

namespace Eternal
{
    NativeWindowHandle::Deleter::Deleter(GuiThread &guiThread):
        m_GuiThread(&guiThread)
    {
    }

    void NativeWindowHandle::Deleter::operator()(HWND handle) const
    {
        auto destroyWindow = [=]
        {
            auto success = DestroyWindow(handle);
            assert(success == TRUE);
        };
        m_GuiThread->Run(destroyWindow);
    }

    NativeWindowHandle::NativeWindowHandle(GuiThread &guiThread, HWND handle):
        m_Handle(handle, Deleter(guiThread))
    {
    }

    HWND NativeWindowHandle::Get() const
    {
        return m_Handle.get();
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
        auto height = static_cast<int>(position[0]);
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
        auto height = static_cast<int>(size[0]);
        auto success = SetWindowPos(m_Handle.get(), nullptr, 0, 0, width, height, flags);
        if (success == FALSE)
        {
            throw LastErrorToException("Failed to set window size");
        }
    }

    void NativeWindowHandle::Show(int code)
    {
        ShowWindow(m_Handle.get(), code);
    }
}
