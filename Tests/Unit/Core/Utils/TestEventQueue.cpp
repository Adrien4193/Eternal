#include <Test.h>

#include <Eternal/Core/Utils/EventQueue.h>

int main()
{
    auto test = CreateTestCase("EventQueue");

    test["On"] = []
    {
        auto events = Eternal::EventQueue();
        events.Push(1);
        events.Push(2);
        events.Push(3);

        auto count = 0;
        events.On<int>([&](auto event) { count += event; });

        Assert(count == 6);
    };

    test["Once"] = []
    {
        auto events = Eternal::EventQueue();
        events.Push(1);
        events.Push(2);
        events.Push(3);

        auto count = 0;
        events.Once<int>([&](auto event) { count += event; });

        Assert(count == 3);
    };

    test["DifferentTypes"] = []
    {
        auto events = Eternal::EventQueue();
        events.Push(1);
        events.Push(2.0F);
        events.Push(3);

        auto count = 0;
        events.On<int>([&](auto event) { count += event; });
        Assert(count == 4);

        auto value = 0.0F;
        events.On<float>([&](auto event) { value += event; });
        Assert(value == 2.0F);

        auto called = false;
        events.On<double>([&](auto) { called = true; });
        AssertFalse(called);
    };

    return test.Run();
}
