# CTI
The constexpr type_info library.

Example usage:
```
#include "cti.h"

int main()
{
    // constexpr string example
    constexpr cti::string str = "hello!";

    static_assert(str.size == 6);
    static_assert(cti::type_info(str).hash() == cti::type_info("hello!").hash());

    // constexpr type_info example
    constexpr cti::type_info_base info = cti::type_info<int>();

    static_assert(info.hash() == cti::type_info<int>().hash());
    static_assert(info.name() == "int");

    std::unordered_map<cti::type_info_base, int> map;

    map[cti::type_info<int>()] = 200;
    map[cti::type_info<short>()] = 100;
    map[cti::type_info("nice")] = 0;

    std::cout << map.at(cti::type_info("nice")) << std::endl; // outputs 0 
}

```
