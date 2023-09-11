#include <Test.h>

#include <Eternal/Math/Products.h>

int main()
{
    using namespace Eternal;

    auto test = CreateTestCase("Products");

    test["Dot"] = []
    {
        auto v1 = Vector<int, 4>(1, 2, 3, 4);
        auto v2 = Vector<int, 4>(5, 6, 7, 8);
        Assert(Dot(v1, v2) == 70);
    };

    test["Cross"] = []
    {
        auto v1 = Vector<int, 3>(1, 2, 3);
        auto v2 = Vector<int, 3>(4, 5, 6);
        Assert(Cross(v1, v2) == Vector<int, 3>(-3, 6, -3));
    };

    test["Multiply"] = []
    {
        auto m1 = Matrix<int, 3, 3>(1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto m2 = Matrix<int, 3, 3>(3, 2, 1, 6, 5, 4, 9, 8, 7);
        auto ref = Matrix<int, 3, 3>(42, 36, 30, 96, 81, 66, 150, 126, 102);
        Assert(Multiply(m1, m2) == ref);
    };

    return test.Run();
}
