#include <Test.h>

#include <Eternal/Core/Math/Matrix.h>

int main()
{
    using namespace Eternal;

    auto test = CreateTestCase("Matrix");

    test["Default"] = []
    {
        auto matrix = Matrix<int, 3, 2>();
        Assert(matrix[0] == 0);
        Assert(matrix[1] == 0);
        Assert(matrix[2] == 0);
        Assert(matrix[3] == 0);
        Assert(matrix[4] == 0);
        Assert(matrix[5] == 0);
    };

    test["Construction"] = []
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

    test["Assignment"] = []
    {
        auto left = Matrix<int, 3, 2>(1, 2, 3, 4, 5, 6);
        auto right = Matrix<int, 3, 2>(7, 8, 9, 10, 11, 12);
        left = right;
        Assert(left == right);
    };

    test["Compare"] = []
    {
        auto left = Matrix<int, 1, 2>(1, 3);
        auto right = Matrix<int, 1, 2>(1, 3);

        Assert(left == right);
        AssertFalse(left != right);
        AssertFalse(left < right);
        Assert(left <= right);
        AssertFalse(right > left);
        Assert(right >= left);

        right[0] += 1;

        Assert(left != right);
        AssertFalse(left == right);
        Assert(left < right);
        Assert(left <= right);
        Assert(right > left);
        Assert(right >= left);
    };

    test["Operators"] = []
    {
        auto left = Matrix<int, 2, 2>(1, 2, 3, 4);
        auto right = Matrix<int, 2, 2>(5, 6, 7, 8);

        Assert(-left == Matrix<int, 2, 2>(-1, -2, -3, -4));
        Assert(+left == left);

        Assert(left + right == Matrix<int, 2, 2>(6, 8, 10, 12));
        Assert(right - left == Matrix<int, 2, 2>(4, 4, 4, 4));
        Assert(left * right == Matrix<int, 2, 2>(5, 12, 21, 32));
        Assert(left * 2 == Matrix<int, 2, 2>(2, 4, 6, 8));
        Assert(2 * left == left * 2);
        Assert(right / 2 == Matrix<int, 2, 2>(2, 3, 3, 4));
        Assert(4 / left == Matrix<int, 2, 2>(4, 2, 1, 1));

        left += right;
        Assert(left == Matrix<int, 2, 2>(6, 8, 10, 12));

        left -= right;
        Assert(left == Matrix<int, 2, 2>(1, 2, 3, 4));

        left *= right;
        Assert(left == Matrix<int, 2, 2>(5, 12, 21, 32));

        left *= 2;
        Assert(left == Matrix<int, 2, 2>(10, 24, 42, 64));

        left /= 2;
        Assert(left == Matrix<int, 2, 2>(5, 12, 21, 32));

        left /= right;
        Assert(left == Matrix<int, 2, 2>(1, 2, 3, 4));
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
