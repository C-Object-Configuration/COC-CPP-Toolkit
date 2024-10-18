#include "coc.hpp"

#define GETTERS(returnType, member)                                                                     \
std::optional<returnType> coc::Struct::member::Get(std::string_view key) {                              \
    if (!map.contains(key.data())) return {};                                                           \
    return map.at(key.data());                                                                          \
}                                                                                                       \
std::optional<returnType> coc::Struct::member::operator[](std::string_view key) { return Get(key); }

GETTERS(coc::Struct, Structs)
GETTERS(bool, Bools)
GETTERS(char, Chars)
GETTERS(int, Ints)
GETTERS(long long int, Longs)
GETTERS(float, Floats)
GETTERS(double, Doubles)
GETTERS(std::string, Strings)