#include <Test.h>

#include <Eternal/Core/Utils/IdGenerator.h>

using namespace Eternal;

int main(int argc, const char **argv)
{
    auto test = CreateTestCase("IdGenerator");

    test["Next"] = []
    {
        auto generator = IdGenerator<int>();

        Assert(generator.Next() == 0);
        Assert(generator.Next() == 1);
        Assert(generator.Next() == 2);
    };

    test["Recycle"] = []
    {
        auto generator = IdGenerator<int>();

        auto id = generator.Next();

        generator.Recycle(id);

        Assert(generator.Next() == id);
    };

    test["Reset"] = []
    {
        auto generator = IdGenerator<int>(2, 10);

        Assert(generator.Next() == 2);
        Assert(generator.Next() == 3);

        generator.Recycle(3);

        generator.Reset();

        Assert(generator.Next() == 2);
        Assert(generator.Next() == 3);

        Assert(generator.GetStart() == 2);
        Assert(generator.GetStop() == 10);
    };

    test["Limits"] = []
    {
        auto generator = IdGenerator<int>(2, 10);

        for (auto i = std::size_t(2); i < std::size_t(10); ++i)
        {
            generator.Next();
        }

        AssertThrow<std::runtime_error>([&] { generator.Next(); });

        auto bytes = IdGenerator<std::uint8_t>();

        for (auto i = std::uint8_t(0); i < std::uint8_t(255); ++i)
        {
            Assert(bytes.Next() == i);
        }

        AssertThrow<std::runtime_error>([&] { bytes.Next(); });
    };

    return test.Run(argc, argv);
}
