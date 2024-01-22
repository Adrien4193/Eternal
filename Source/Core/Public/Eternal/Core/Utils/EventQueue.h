#pragma once

#include <any>
#include <vector>

namespace Eternal
{
    class EventQueue
    {
    private:
        std::vector<std::any> m_Events;

    public:
        void Clear()
        {
            m_Events.clear();
        }

        void Push(std::any event)
        {
            m_Events.push_back(std::move(event));
        }

        template<typename EventType, typename CallableType>
        void On(CallableType &&callable) const
        {
            for (const auto &event : m_Events)
            {
                const auto *value = std::any_cast<EventType>(&event);
                if (value)
                {
                    std::forward<CallableType>(callable)(*value);
                }
            }
        }

        template<typename EventType, typename CallableType>
        void Once(CallableType &&callable) const
        {
            for (auto i = m_Events.rbegin(); i != m_Events.rend(); ++i)
            {
                const auto &event = *i;
                const auto *value = std::any_cast<EventType>(&event);
                if (value)
                {
                    std::forward<CallableType>(callable)(*value);
                    return;
                }
            }
        }
    };
}
