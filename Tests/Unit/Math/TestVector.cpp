#include <Test.h>

#include <Eternal/Math/Vector.h>

int main()
{
    auto test = CreateTestCase("Vector");

    test["Construction"] = [&]
    {
        auto v = Eternal::Vector3(1, 2, 3);

        Assert(v[0] == 1);
        Assert(v[1] == 2);
        Assert(v[2] == 3);

        auto empty = Eternal::Vector3();

        Assert(empty[0] == 0.0f);
        Assert(empty[1] == 0.0f);
        Assert(empty[2] == 0.0f);

        auto partial = Eternal::Vector3(1);

        Assert(partial[0] == 1.0f);
        Assert(partial[1] == 0.0f);
        Assert(partial[2] == 0.0f);
    };

    test["Assignment"] = [&]
    {
        auto a = Eternal::Vector3(1, 2, 3);
        auto b = Eternal::Vector3(4, 5, 6);

        a = b;
        Assert(a == b);
    };

    test["Compare"] = []
    {
        auto a = Eternal::Vector3(1, 2, 3);
        auto b = Eternal::Vector3(1, 2, 3);

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
        auto a = Eternal::Vector3(1, 2, 3);
        auto b = Eternal::Vector3(4, 5, 6);

        Assert(-a == Eternal::Vector3(-1, -2, -3));
        Assert(+a == a);

        Assert(a + b == Eternal::Vector3(5, 7, 9));
        Assert(b - a == Eternal::Vector3(3, 3, 3));
        Assert(a * b == Eternal::Vector3(4, 10, 18));
        Assert(a / b == Eternal::Vector3(0.25f, 0.4f, 0.5f));

        a += b;
        Assert(a == Eternal::Vector3(5, 7, 9));

        a -= b;
        Assert(a == Eternal::Vector3(1, 2, 3));

        a *= b;
        Assert(a == Eternal::Vector3(4, 10, 18));

        a *= 2;
        Assert(a == Eternal::Vector3(8, 20, 36));
    };

    test["Iterate"] = []
    {
        auto v = Eternal::Vector3(1, 2, 3);

        auto count = 0.0f;
        for (auto i : v)
        {
            count += i;
        }

        Assert(count == 6.0f);
    };

    return test.Run();
}
