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

        constexpr auto GetData() const -> const T *
        {
            return m_Components;
        }

        constexpr auto GetData() -> T *
        {
            return m_Components;
        }

        constexpr auto operator[](std::size_t index) const -> const T &
        {
            assert(index < ComponentCount);
            return m_Components[index];
        }

        constexpr auto operator[](std::size_t index) -> T &
        {
            assert(index < ComponentCount);
            return m_Components[index];
        }

        constexpr auto operator()(std::size_t row, std::size_t column) const -> const T &
        {
            assert(row < RowCount && column < ColumnCount);
            return m_Components[row * RowSize + column];
        }

        constexpr auto operator()(std::size_t row, std::size_t column) -> T &
        {
            assert(row < RowCount && column < ColumnCount);
            return m_Components[row * RowSize + column];
        }

        constexpr auto operator<=>(const Matrix &) const = default;
    };

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto begin(const Eternal::Matrix<T, M, N> &value) -> const T *
    {
        return value.GetData();
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto begin(Eternal::Matrix<T, M, N> &value) -> T *
    {
        return value.GetData();
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto end(const Eternal::Matrix<T, M, N> &value) -> const T *
    {
        return value.GetData() + value.ComponentCount;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto end(Eternal::Matrix<T, M, N> &value) -> T *
    {
        return value.GetData() + value.ComponentCount;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto operator-(Matrix<T, M, N> value) -> Matrix<T, M, N>
    {
        for (auto i = std::size_t(0); i < value.ComponentCount; ++i)
        {
            value[i] = -value[i];
        }
        return value;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto operator+(Matrix<T, M, N> value) -> Matrix<T, M, N>
    {
        for (auto i = std::size_t(0); i < value.ComponentCount; ++i)
        {
            value[i] = +value[i];
        }
        return value;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto operator+=(Matrix<T, M, N> &left, const Matrix<T, M, N> &right) -> Matrix<T, M, N> &
    {
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] += right[i];
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto operator+(Matrix<T, M, N> left, const Matrix<T, M, N> &right) -> Matrix<T, M, N>
    {
        return left += right;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto operator-=(Matrix<T, M, N> &left, const Matrix<T, M, N> &right) -> Matrix<T, M, N> &
    {
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] -= right[i];
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto operator-(Matrix<T, M, N> left, const Matrix<T, M, N> &right) -> Matrix<T, M, N>
    {
        return left -= right;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto operator*=(Matrix<T, M, N> &left, const Matrix<T, M, N> &right) -> Matrix<T, M, N> &
    {
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] *= right[i];
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N, typename U>
    constexpr auto operator*=(Matrix<T, M, N> &left, U right) -> Matrix<T, M, N> &
    {
        auto factor = static_cast<T>(right);
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] *= factor;
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto operator*(Matrix<T, M, N> left, const Matrix<T, M, N> &right) -> Matrix<T, M, N>
    {
        return left *= right;
    }

    template<typename T, std::size_t M, std::size_t N, typename U>
    constexpr auto operator*(Matrix<T, M, N> left, U right) -> Matrix<T, M, N>
    {
        return left *= right;
    }

    template<typename T, std::size_t M, std::size_t N, typename U>
    constexpr auto operator*(U left, Matrix<T, M, N> right) -> Matrix<T, M, N>
    {
        return right *= left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto operator/=(Matrix<T, M, N> &left, const Matrix<T, M, N> &right) -> Matrix<T, M, N> &
    {
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] /= right[i];
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N, typename U>
    constexpr auto operator/=(Matrix<T, M, N> &left, U right) -> Matrix<T, M, N> &
    {
        auto factor = static_cast<T>(right);
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            left[i] /= factor;
        }
        return left;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr auto operator/(Matrix<T, M, N> left, const Matrix<T, M, N> &right) -> Matrix<T, M, N>
    {
        return left /= right;
    }

    template<typename T, std::size_t M, std::size_t N, typename U>
    constexpr auto operator/(Matrix<T, M, N> left, U right) -> Matrix<T, M, N>
    {
        return left /= right;
    }

    template<typename T, std::size_t M, std::size_t N, typename U>
    constexpr auto operator/(U left, Matrix<T, M, N> right) -> Matrix<T, M, N>
    {
        auto factor = static_cast<T>(left);
        for (auto i = std::size_t(0); i < right.ComponentCount; ++i)
        {
            right[i] = factor / right[i];
        }
        return right;
    }
}
