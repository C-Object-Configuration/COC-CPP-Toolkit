#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <optional>

namespace coc {
    class Struct;
    std::optional<Struct> Load(std::string data);

    #define TYPE(type, member)                                  \
    class member {                                              \
    friend std::optional<Struct> Load(std::string data);        \
    public:                                                     \
        std::optional<type> Get(std::string_view key);          \
        std::optional<type> operator[](std::string_view key);   \
    private:                                                    \
        std::unordered_map<std::string, type> map;            \
    } member;

    class Struct {
    friend std::optional<Struct> Load(std::string data);
    public:
        TYPE(coc::Struct, Structs)
        TYPE(bool, Bools)
        TYPE(char, Chars)
        TYPE(int, Ints)
        TYPE(long long int, Longs)
        TYPE(float, Floats)
        TYPE(double, Doubles)
        TYPE(std::string, Strings)

    private:
        bool tokenize(std::string_view data, int &index, std::string stringedType, std::string &key, std::string &value, bool(*hasValue)(std::string_view data, int &index, std::string &key, std::string &value));
        bool tokenizeType(std::string_view data, int &index, std::string &type);
        bool tokenizeKey(std::string_view data, int &index, std::string &key);
        bool tokenizeValue(std::string_view data, int &index, std::string &key, std::string &value, bool(*hasValue)(std::string_view data, int &index, std::string &key, std::string &value));
    };
}