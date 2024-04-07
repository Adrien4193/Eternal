#pragma once

#include <memory>
#include <string_view>

#include <Windows.h>

#include <Eternal/Core/Math/Types.h>

#include "GuiThread.h"

namespace Eternal
{
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

    public:
        explicit NativeWindowHandle(GuiThread &guiThread, HWND handle);

        HWND Get() const;
        void SetTitle(std::string_view title);
        void SetPosition(Vector2 position);
        void Resize(Vector2 size);
        void Show(int code);
    };
}
