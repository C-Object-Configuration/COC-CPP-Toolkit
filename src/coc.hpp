#pragma once
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace coc {
    class Struct;
    std::optional<Struct> Open(std::string path);
    std::optional<Struct> Load(std::string data);

    #define TYPE(type, name)                                                \
    class name {                                                            \
    friend std::optional<Struct> Load(std::string data);                    \
    public:                                                                 \
        std::optional<type> Get(std::string_view key);                      \
        std::optional<type> operator[](std::string_view key);               \
        std::unordered_map<std::string, type> map;                          \
    } name;

    #define TYPES(type, name, arrayName)    \
    TYPE(type, name)                        \
    TYPE(std::vector<type>, arrayName)

    class Struct {
    friend std::optional<Struct> Load(std::string data);
    public:
        TYPES(coc::Struct, Structs, StructArrays)
        TYPES(bool, Bools, BoolArrays)
        TYPES(char, Chars, CharArrays)
        TYPES(int, Ints, IntArrays)
        TYPES(long long int, Longs, LongArrays)
        TYPES(float, Floats, FloatArrays)
        TYPES(double, Doubles, DoubleArrays)
        TYPES(std::string, Strings, StringArrays)

    private:
        enum tokenizeValueCallback {
            Fail,
            Single,
            Array
        };
        tokenizeValueCallback tokenize(std::string_view data, int &index, std::string stringedType, std::string &key, std::vector<std::string> &values, bool(*hasValue)(std::string_view data, int &index, bool isArray, std::string &key, std::string &value));
        bool tokenizeType(std::string_view data, int &index, std::string &type);
        bool tokenizeKey(std::string_view data, int &index, std::string &key);
        tokenizeValueCallback tokenizeValue(std::string_view data, int &index, std::string &key, std::vector<std::string> &values, bool(*hasValue)(std::string_view data, int &index, bool isArray, std::string &key, std::string &value));
    };
}