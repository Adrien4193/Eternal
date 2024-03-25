#include <Test.h>

#include <Eternal/Core/Window/WindowManager.h>

using namespace Eternal;

int main()
{
    auto test = CreateTestCase("Window");

    test["Manager"] = []
    {
        auto dummy = 0;
        auto nativeHandle = static_cast<void *>(&dummy);
        auto events = std::vector<WindowEvent>{WindowResize({1, 2}), WindowMove({3, 4})};
        auto title = std::string("Test");
        auto position = Vector2(1, 2);
        auto size = Vector2(3, 4);

        auto windowHandleFactory = [&](const auto &)
        {
            return WindowHandle{
                .NativePtr = nativeHandle,
                .Poll = [&] { return events; },
                .SetTitle = [&](auto value) { title = value; },
                .SetPosition = [&](auto value) { position = value; },
                .Resize = [&](auto value) { size = value; },
            };
        };

        auto windowManagerPrivate = WindowManagerPrivate(windowHandleFactory);
        auto windowManager = WindowManager(windowManagerPrivate);

        auto &window = windowManager.AddWindow({title, position, size});

        Assert(window.GetId() == 0);
        Assert(window.GetNativeHandle() == nativeHandle);
        Assert(window.GetTitle() == title);
        Assert(window.GetPosition() == position);
        Assert(window.GetSize() == size);

        Assert(window.GetEvents().empty());

        window.SetTitle("A");
        Assert(title == "A");

        window.SetPosition({3, 4});
        Assert(position == Vector2(3, 4));

        window.Resize({1, 2});
        Assert(size == Vector2(1, 2));

        windowManagerPrivate.PollWindows();

        auto polledEvents = window.GetEvents();

        Assert(polledEvents.size() == 2);

        Assert(std::get<WindowResize>(polledEvents[0]).Size == Vector2{1, 2});
        Assert(std::get<WindowMove>(polledEvents[1]).Position == Vector2{3, 4});
    };

    return test.Run();
}
