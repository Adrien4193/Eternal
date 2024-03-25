#include <Test.h>

#include <Eternal/Core/Math/Products.h>

using namespace Eternal;

int main()
{
    auto test = CreateTestCase("Products");

    test["Dot"] = []
    {
        auto left = Vector<int, 4>(1, 2, 3, 4);
        auto right = Vector<int, 4>(5, 6, 7, 8);
        Assert(Dot(left, right) == 70);
    };

    test["Cross"] = []
    {
        auto left = Vector<int, 3>(1, 2, 3);
        auto right = Vector<int, 3>(4, 5, 6);
        auto ref = Vector<int, 3>(-3, 6, -3);
        Assert(Cross(left, right) == ref);
    };

    test["Multiply"] = []
    {
        auto left = Matrix<int, 3, 3>(1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto right = Matrix<int, 3, 3>(3, 2, 1, 6, 5, 4, 9, 8, 7);
        auto ref = Matrix<int, 3, 3>(42, 36, 30, 96, 81, 66, 150, 126, 102);
        Assert(Multiply(left, right) == ref);
    };

    return test.Run();
}
