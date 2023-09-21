#pragma once

#include <vector>

namespace Eternal
{
    template<typename T>
    class IdGenerator
    {
    private:
        T m_Counter = 0;
        std::vector<T> m_AvailableIds;

    public:
        T Next()
        {
            if (m_AvailableIds.empty())
            {
                return m_Counter++;
            }
            auto id = m_AvailableIds.back();
            m_AvailableIds.pop_back();
            return id;
        }

        void Recycle(T id)
        {
            m_AvailableIds.push_back(id);
        }
    };
}
