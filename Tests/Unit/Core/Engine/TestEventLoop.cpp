#include <Test.h>

#include <Eternal/Core/Engine/EventLoop.h>

using namespace Eternal;

int main()
{
    auto test = CreateTestCase("EventLoop");

    test["Stop"] = []
    {
        auto eventLoopPrivate = EventLoopPrivate();
        auto eventLoop = EventLoop(eventLoopPrivate);

        Assert(!eventLoopPrivate.Running);
    };

    return test.Run();
}
