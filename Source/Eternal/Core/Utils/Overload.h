#pragma once

namespace Eternal
{
    template<typename... Ts>
    struct Overload : Ts...
    {
        using Ts::operator()...;
    };
}
