#include <Test.h>

#include <Eternal/Utils/IdGenerator.h>

int main()
{
    auto test = CreateTestCase("IdGenerator");

    test["Next"] = []
    {
        auto generator = Eternal::IdGenerator<int>();
        Assert(generator.Next() == 0);
        Assert(generator.Next() == 1);
        Assert(generator.Next() == 2);
    };

    test["Recycle"] = []
    {
        auto generator = Eternal::IdGenerator<int>();
        auto id = generator.Next();
        generator.Recycle(id);
        Assert(generator.Next() == id);
    };

    return test.Run();
}
