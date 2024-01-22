#include <Test.h>

#include <Eternal/Core/Engine/Window.h>

int main()
{
    using namespace Eternal;

    auto test = CreateTestCase("Window");

    test["Properties"] = []
    {
        auto id = std::size_t(1);

        auto properties = Eternal::WindowProperties();
        properties.Title = "Test";
        properties.Position = {1.0F, 2.0F};
        properties.Size = {3.0F, 4.0F};

        auto handle = Eternal::WindowHandle();
        handle.NativePtr = &id;

        auto events = Eternal::EventQueue();

        auto window = Eternal::Window(id, handle, properties, events);

        Assert(window.GetId() == id);
        Assert(window.GetNativeHandle() == handle.NativePtr);
        Assert(window.GetTitle() == properties.Title);
        Assert(window.GetPosition() == properties.Position);
        Assert(window.GetSize() == properties.Size);
    };

    test["Handler"] = []
    {
        auto id = std::size_t(0);

        auto properties = Eternal::WindowProperties();
        auto ref = Eternal::WindowProperties();
        ref.Title = "Test";
        ref.Position = {1.0F, 2.0F};
        ref.Size = {3.0F, 4.0F};

        auto handle = Eternal::WindowHandle();
        handle.SetTitle = [&](auto title) { properties.Title = title; };
        handle.SetPosition = [&](auto position) { properties.Position = position; };
        handle.Resize = [&](auto size) { properties.Size = size; };

        auto events = Eternal::EventQueue();

        auto window = Eternal::Window(id, handle, properties, events);

        window.SetTitle(ref.Title);
        window.SetPosition(ref.Position);
        window.Resize(ref.Size);

        Assert(properties.Title == ref.Title);
        Assert(properties.Position == ref.Position);
        Assert(properties.Size == ref.Size);
    };

    test["Events"] = []
    {
        auto id = std::size_t(0);
        auto properties = Eternal::WindowProperties();
        auto handle = Eternal::WindowHandle();
        auto events = Eternal::EventQueue();

        auto window = Eternal::Window(id, handle, properties, events);

        events.Push(1);
        events.Push(2);
        events.Push(2.0F);

        auto count = int();

        window.On<int>([&](auto value) { count += value; });
        Assert(count == 3);

        window.On<float>([&](auto value) { count += static_cast<int>(value); });
        Assert(count == 5);

        window.On<double>([&](auto value) { count += static_cast<int>(value); });
        Assert(count == 5);

        window.Once<int>([&](auto value) { count += value; });
        Assert(count == 7);
    };

    return test.Run();
}
