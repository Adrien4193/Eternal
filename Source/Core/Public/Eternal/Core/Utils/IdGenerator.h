#pragma once

#include <vector>

namespace Eternal
{
    template<typename T>
    class IdGenerator
    {
    private:
        T m_Counter = 0;
        std::vector<T> m_RecycledIds;

    public:
        T Next()
        {
            if (m_RecycledIds.empty())
            {
                return m_Counter++;
            }
            auto id = m_RecycledIds.back();
            m_RecycledIds.pop_back();
            return id;
        }

        void Recycle(T id)
        {
            m_RecycledIds.push_back(id);
        }
    };
}
