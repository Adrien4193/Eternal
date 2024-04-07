#pragma once

#include "Matrix.h"

namespace Eternal
{
    using Matrix2 = Matrix<float, 2, 2>;
    using Matrix3 = Matrix<float, 3, 3>;
    using Matrix4 = Matrix<float, 4, 4>;

    template<typename T, std::size_t N>
    using Vector = Matrix<T, N, 1>;

    using Vector2 = Vector<float, 2>;
    using Vector3 = Vector<float, 3>;
    using Vector4 = Vector<float, 4>;
}
