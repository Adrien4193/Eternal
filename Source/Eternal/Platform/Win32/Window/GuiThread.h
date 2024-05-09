#pragma once

#include <concepts>
#include <functional>
#include <future>
#include <thread>
#include <type_traits>

#include <Windows.h>

namespace Eternal
{
    class GuiThread
    {
    private:
        DWORD m_Id;
        std::jthread m_Thread;

    public:
        explicit GuiThread(DWORD id, std::jthread thread);
        ~GuiThread();

        GuiThread(const GuiThread &) = delete;
        GuiThread &operator=(const GuiThread &) = delete;
        GuiThread(GuiThread &&) = default;
        GuiThread &operator=(GuiThread &&) = default;

        auto Run(std::invocable<> auto &&task) const -> decltype(task())
        {
            using ResultType = decltype(task());

            auto promise = std::promise<ResultType>();
            auto future = promise.get_future();

            auto wrapper = [&]
            {
                try
                {
                    if constexpr (std::is_void_v<ResultType>)
                    {
                        task();
                        promise.set_value();
                    }
                    else
                    {
                        promise.set_value(task());
                    }
                }
                catch (...)
                {
                    promise.set_exception(std::current_exception());
                }
            };

            auto function = std::function<void()>(wrapper);

            Schedule(function);

            return future.get();
        }

    private:
        void Schedule(const std::function<void()> &task) const;
    };

    GuiThread StartGuiThread();
}
