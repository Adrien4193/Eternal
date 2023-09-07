#include <Test.h>

#include <Eternal/Math/Matrix.h>

int main()
{
    using namespace Eternal;

    auto test = CreateTestCase("Matrix");

    test["Construction"] = [&]
    {
        auto matrix = Matrix<int, 3, 2>(0, 1, 2, 3, 4, 5);
        Assert(matrix[0] == 0);
        Assert(matrix[1] == 1);
        Assert(matrix[2] == 2);
        Assert(matrix[3] == 3);
        Assert(matrix[4] == 4);
        Assert(matrix[5] == 5);
        Assert(matrix(0, 0) == 0);
        Assert(matrix(0, 1) == 1);
        Assert(matrix(1, 0) == 2);
        Assert(matrix(1, 1) == 3);
        Assert(matrix(2, 0) == 4);
        Assert(matrix(2, 1) == 5);
    };

    test["Assignment"] = [&]
    {
        auto a = Matrix<int, 3, 2>(1, 2, 3, 4, 5, 6);
        auto b = Matrix<int, 3, 2>(7, 8, 9, 10, 11, 12);

        a = b;
        Assert(a == b);
    };

    test["Compare"] = []
    {
        auto a = Matrix<float, 1, 2>(1, 3);
        auto b = Matrix<float, 1, 2>(1, 3);

        Assert(a == b);
        AssertFalse(a != b);
        AssertFalse(a < b);
        Assert(a <= b);
        AssertFalse(b > a);
        Assert(b >= a);

        b[0] += 1;

        Assert(a != b);
        AssertFalse(a == b);
        Assert(a < b);
        Assert(a <= b);
        Assert(b > a);
        Assert(b >= a);
    };

    test["Operators"] = [&]
    {
        auto a = Matrix<int, 2, 2>(1, 2, 3, 4);
        auto b = Matrix<int, 2, 2>(5, 6, 7, 8);

        Assert(-a == Matrix<int, 2, 2>(-1, -2, -3, -4));
        Assert(+a == a);

        Assert(a + b == Matrix<int, 2, 2>(6, 8, 10, 12));
        Assert(b - a == Matrix<int, 2, 2>(4, 4, 4, 4));
        Assert(a * b == Matrix<int, 2, 2>(5, 12, 21, 32));
        Assert(a * 2 == Matrix<int, 2, 2>(2, 4, 6, 8));
        Assert(b / 2 == Matrix<int, 2, 2>(2, 3, 3, 4));

        a += b;
        Assert(a == Matrix<int, 2, 2>(6, 8, 10, 12));

        a -= b;
        Assert(a == Matrix<int, 2, 2>(1, 2, 3, 4));

        a *= b;
        Assert(a == Matrix<int, 2, 2>(5, 12, 21, 32));

        a *= 2;
        Assert(a == Matrix<int, 2, 2>(10, 24, 42, 64));

        a /= 2;
        Assert(a == Matrix<int, 2, 2>(5, 12, 21, 32));

        a /= b;
        Assert(a == Matrix<int, 2, 2>(1, 2, 3, 4));
    };

    test["Iterate"] = []
    {
        auto matrix = Matrix<int, 2, 3>(1, 2, 3, 4, 5, 6);

        auto count = 0;
        for (auto i : matrix)
        {
            count += i;
        }

        Assert(count == 21);
    };

    return test.Run();
}
