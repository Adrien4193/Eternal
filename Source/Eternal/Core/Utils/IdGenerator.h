#pragma once

#include <limits>
#include <stdexcept>
#include <vector>

namespace Eternal
{
    template<typename T>
    class IdGenerator
    {
    private:
        T m_Min;
        T m_Max;
        T m_Counter;
        std::vector<T> m_RecycledIds;

    public:
        explicit IdGenerator(T min = T(0), T max = std::numeric_limits<T>::max()):
            m_Min(min),
            m_Max(max),
            m_Counter(min)
        {
        }

        T GetMin() const
        {
            return m_Min;
        }

        T GetMax() const
        {
            return m_Max;
        }

        void Reset()
        {
            m_Counter = m_Min;
            m_RecycledIds.clear();
        }

        T Next()
        {
            if (!m_RecycledIds.empty())
            {
                auto id = m_RecycledIds.back();
                m_RecycledIds.pop_back();
                return id;
            }

            if (m_Counter >= m_Max)
            {
                throw std::runtime_error("No more IDs available");
            }

            return m_Counter++;
        }

        void Recycle(T id)
        {
            m_RecycledIds.push_back(id);
        }
    };
}
