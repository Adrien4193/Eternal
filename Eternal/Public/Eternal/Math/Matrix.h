#pragma once

#include <cassert>
#include <cstddef>
#include <type_traits>

namespace Eternal
{
    template<typename T, std::size_t M, std::size_t N>
    requires(std::is_arithmetic_v<T> && M > 0 && N > 0)
    class Matrix
    {
    public:
        using ComponentType = T;

        static constexpr auto RowCount = M;
        static constexpr auto RowSize = N;
        static constexpr auto ColumnCount = N;
        static constexpr auto ColumnSize = M;
        static constexpr auto ComponentCount = M * N;

    private:
        T m_Components[ComponentCount];

    public:
        explicit constexpr Matrix() = default;

        template<typename... Args>
        requires(sizeof...(Args) == ComponentCount && (std::is_same_v<Args, T> && ...))
        constexpr Matrix(Args... args):
            m_Components{args...}
        {
        }

        constexpr const T *GetData() const
        {
            return static_cast<const T *>(m_Components);
        }

        constexpr T *GetData()
        {
            return static_cast<T *>(m_Components);
        }

        constexpr const T &operator[](std::size_t index) const
        {
            assert(index < ComponentCount);
            return m_Components[index];
        }

        constexpr T &operator[](std::size_t index)
        {
            assert(index < ComponentCount);
            return m_Components[index];
        }

        constexpr const T &operator()(std::size_t row, std::size_t column) const
        {
            assert(row < RowCount && column < ColumnCount);
            return m_Components[row * RowSize + column];
        }

        constexpr T &operator()(std::size_t row, std::size_t column)
        {
            assert(row < RowCount && column < ColumnCount);
            return m_Components[row * RowSize + column];
        }

        constexpr auto operator<=>(const Matrix &) const = default;
    };

    template<typename T, std::size_t M, std::size_t N>
    constexpr const T *begin(const Eternal::Matrix<T, M, N> &value)
    {
        return value.GetData();
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr T *begin(Eternal::Matrix<T, M, N> &value)
    {
        return value.GetData();
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr const T *end(const Eternal::Matrix<T, M, N> &value)
    {
        return value.GetData() + value.ComponentCount;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr T *end(Eternal::Matrix<T, M, N> &value)
    {
        return value.GetData() + value.ComponentCount;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> operator-(Matrix<T, M, N> value)
    {
        for (auto i = std::size_t(0); i < value.ComponentCount; ++i)
        {
            value[i] = -value[i];
        }
        return value;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> operator+(Matrix<T, M, N> value)
    {
        for (auto i = std::size_t(0); i < value.ComponentCount; ++i)
        {
            value[i] = +value[i];
        }
        return value;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> &operator+=(Matrix<T, M, N> &left, const Matrix<T, M, N> &right)
    {
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] += right[i];
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> operator+(Matrix<T, M, N> left, const Matrix<T, M, N> &right)
    {
        return left += right;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> &operator-=(Matrix<T, M, N> &left, const Matrix<T, M, N> &right)
    {
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] -= right[i];
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> operator-(Matrix<T, M, N> left, const Matrix<T, M, N> &right)
    {
        return left -= right;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> &operator*=(Matrix<T, M, N> &left, const Matrix<T, M, N> &right)
    {
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] *= right[i];
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> &operator*=(Matrix<T, M, N> &left, T right)
    {
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] *= right;
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> operator*(Matrix<T, M, N> left, const Matrix<T, M, N> &right)
    {
        return left *= right;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> operator*(Matrix<T, M, N> left, T right)
    {
        return left *= right;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> operator*(T left, Matrix<T, M, N> right)
    {
        return right *= left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> &operator/=(Matrix<T, M, N> &left, const Matrix<T, M, N> &right)
    {
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] /= right[i];
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> &operator/=(Matrix<T, M, N> &left, T right)
    {
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] /= right;
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> operator/(Matrix<T, M, N> left, const Matrix<T, M, N> &right)
    {
        return left /= right;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> operator/(Matrix<T, M, N> left, T right)
    {
        return left /= right;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr Matrix<T, M, N> operator/(T left, Matrix<T, M, N> right)
    {
        for (auto i = std::size_t(0); i < right.ComponentCount; ++i)
        {
            right[i] = left / right[i];
        }
        return right;
    }
}
