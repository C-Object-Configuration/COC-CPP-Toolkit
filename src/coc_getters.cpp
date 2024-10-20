#include "coc.hpp"

#define GETTER(type, name)                                                                      \
std::optional<type> coc::Struct::name::Get(std::string_view key) {                              \
    if (!map.contains(key.data())) return {};                                                   \
    return map.at(key.data());                                                                  \
}                                                                                               \
std::optional<type> coc::Struct::name::operator[](std::string_view key) { return Get(key); }

#define GETTERS(type, name, arrayName)  \
GETTER(type, name)                      \
GETTER(std::vector<type>, arrayName)

GETTERS(coc::Struct, Structs, StructArrays)
GETTERS(bool, Bools, BoolArrays)
GETTERS(char, Chars, CharArrays)
GETTERS(int, Ints, IntArrays)
GETTERS(long long int, Longs, LongArrays)
GETTERS(float, Floats, FloatArrays)
GETTERS(double, Doubles, DoubleArrays)
GETTERS(std::string, Strings, StringArrays)