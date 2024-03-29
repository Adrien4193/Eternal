#pragma once

#include "Types.h"

namespace Eternal
{
    template<typename T, std::size_t N>
    constexpr T Dot(const Vector<T, N> &left, const Vector<T, N> &right)
    {
        auto result = T(0);
        for (auto i = std::size_t(0); i < left.ComponentCount; ++i)
        {
            result += left[i] * right[i];
        }
        return result;
    }

    template<typename T>
    constexpr Vector<T, 3> Cross(const Vector<T, 3> &left, const Vector<T, 3> &right)
    {
        return {left[1] * right[2] - left[2] * right[1], left[2] * right[0] - left[0] * right[2], left[0] * right[1] - left[1] * right[0]};
    }

    template<typename T, std::size_t M1, std::size_t N1, std::size_t N2>
    constexpr Matrix<T, M1, N2> Multiply(const Matrix<T, M1, N1> &left, const Matrix<T, N1, N2> &right)
    {
        auto result = Matrix<T, M1, N2>();
        for (auto i = std::size_t(0); i < left.RowCount; ++i)
        {
            for (auto j = std::size_t(0); j < right.RowCount; ++j)
            {
                for (auto k = std::size_t(0); k < right.ColumnCount; ++k)
                {
                    result(i, j) += left(i, k) * right(k, j);
                }
            }
        }
        return result;
    }
}
