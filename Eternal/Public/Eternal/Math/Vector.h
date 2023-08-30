#pragma once

#include <cassert>
#include <cstddef>
#include <type_traits>

namespace Eternal
{
    template<typename T, std::size_t N>
    requires(N > 0)
    class Vector
    {
    private:
        T m_Components[N];

    public:
        using ComponentType = T;

        static constexpr std::size_t ComponentCount = N;

        template<typename... Args>
        requires(sizeof...(Args) <= N && (std::is_convertible_v<Args, T> && ...))
        constexpr Vector(Args ...args):
            m_Components{static_cast<T>(args)...}
        {
        }

        constexpr const T *GetData() const
        {
            return m_Components;
        }

        constexpr T *GetData()
        {
            return m_Components;
        }

        constexpr std::size_t GetSize() const
        {
            return ComponentCount;
        }

        constexpr const T &operator[](std::size_t index) const
        {
            assert(index < N);
            return m_Components[index];
        }

        constexpr T &operator[](std::size_t index)
        {
            assert(index < N);
            return m_Components[index];
        }

        constexpr auto operator<=>(const Vector &) const = default;
    };

    template<typename T, std::size_t N>
    constexpr Vector<T, N> operator-(Vector<T, N> value)
    {
        for (auto i = std::size_t(0); i < N; ++i)
        {
            value[i] = -value[i];
        }
        return value;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> operator+(Vector<T, N> value)
    {
        for (auto i = std::size_t(0); i < N; ++i)
        {
            value[i] = +value[i];
        }
        return value;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> &operator+=(Vector<T, N> &left, const Vector<T, N> &right)
    {
        for (auto i = std::size_t(0); i < N; ++i)
        {
            left[i] += right[i];
        }
        return left;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> operator+(Vector<T, N> left, const Vector<T, N> &right)
    {
        return left += right;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> &operator-=(Vector<T, N> &left, const Vector<T, N> &right)
    {
        for (auto i = std::size_t(0); i < N; ++i)
        {
            left[i] -= right[i];
        }
        return left;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> operator-(Vector<T, N> left, const Vector<T, N> &right)
    {
        return left -= right;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> &operator*=(Vector<T, N> &left, const Vector<T, N> &right)
    {
        for (auto i = std::size_t(0); i < N; ++i)
        {
            left[i] *= right[i];
        }
        return left;
    }

    template<typename T, std::size_t N, typename U>
    constexpr Vector<T, N> &operator*=(Vector<T, N> &left, U right)
    {
        auto factor = static_cast<T>(right);
        for (auto i = std::size_t(0); i < N; ++i)
        {
            left[i] *= factor;
        }
        return left;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> operator*(Vector<T, N> left, const Vector<T, N> &right)
    {
        return left *= right;
    }

    template<typename T, std::size_t N, typename U>
    constexpr Vector<T, N> operator*(Vector<T, N> left, U right)
    {
        return left *= right;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> &operator/=(Vector<T, N> &left, const Vector<T, N> &right)
    {
        for (auto i = std::size_t(0); i < N; ++i)
        {
            left[i] /= right[i];
        }
        return left;
    }

    template<typename T, std::size_t N, typename U>
    constexpr Vector<T, N> &operator/=(Vector<T, N> &left, U right)
    {
        auto factor = static_cast<T>(right);
        for (auto i = std::size_t(0); i < N; ++i)
        {
            left[i] /= factor;
        }
        return left;
    }

    template<typename T, std::size_t N>
    constexpr Vector<T, N> operator/(Vector<T, N> left, const Vector<T, N> &right)
    {
        return left /= right;
    }

    template<typename T, std::size_t N, typename U>
    constexpr Vector<T, N> operator/(Vector<T, N> left, U right)
    {
        return left /= right;
    }

    using Vector2 = Vector<float, 2>;
    using Vector3 = Vector<float, 3>;
    using Vector4 = Vector<float, 4>;
}

namespace std
{
    template<typename T, std::size_t N>
    constexpr const T *begin(const Eternal::Vector<T, N> &value)
    {
        return value.GetData();
    }

    template<typename T, std::size_t N>
    constexpr T *begin(Eternal::Vector<T, N> &value)
    {
        return value.GetData();
    }

    template<typename T, std::size_t N>
    constexpr const T *end(const Eternal::Vector<T, N> &value)
    {
        return value.GetData() + value.GetSize();
    }

    template<typename T, std::size_t N>
    constexpr T *end(Eternal::Vector<T, N> &value)
    {
        return value.GetData() + value.GetSize();
    }
}
