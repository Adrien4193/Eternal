#include <Eternal/Core/Factory.h>

#include <iostream>

int main()
{
    auto application = Eternal::CreateApplication();
    application.OnStart([] { std::cout << "Test start.\n"; });
    application.OnUpdate([] { std::cout << "Test update.\n"; });
    application.OnStop([] { std::cout << "Test stop.\n"; });
    application.Run();
    return 0;
}
