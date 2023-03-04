# CTI
The constexpr type_info library.

Example usage:
'''
static_assert(cti::type_info<char>() == cti::type_info_decayed<const char>(), "something really bad happened...");
static_assert(cti::type_info<char>() != cti::type_info_decayed<const int>(), "something really bad happened2...");

std::unordered_map<cti::type_info_base, cti::string> map;
map[cti::type_info<int>()] = cti::type_info<int>().name();
std::cout << map[cti::type_info<int>()] << std::endl; // should output int
'''