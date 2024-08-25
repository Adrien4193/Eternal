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
        T m_Start;
        T m_Stop;
        T m_Counter;
        std::vector<T> m_RecycledIds;

    public:
        explicit IdGenerator(T start = T(0), T stop = std::numeric_limits<T>::max()):
            m_Start(start),
            m_Stop(stop),
            m_Counter(start)
        {
        }

        T GetStart() const
        {
            return m_Start;
        }

        T GetStop() const
        {
            return m_Stop;
        }

        void Reset()
        {
            m_Counter = m_Start;
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

            if (m_Counter >= m_Stop)
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
