#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <optional>

namespace etcl {
    struct Var {
        std::string Key = "";
        std::string Value = "";
    };

    class Object {
    friend std::optional<Object> Load(std::string data);
    public:
        std::optional<Object> GetObject(std::string_view key);
        std::optional<bool> GetBool(std::string_view key);
        std::optional<char> GetChar(std::string_view key);
        std::optional<int> GetInt(std::string_view key);
        std::optional<long long int> GetLong(std::string_view key);
        std::optional<float> GetFloat(std::string_view key);
        std::optional<double> GetDouble(std::string_view key);
        std::optional<std::string> GetString(std::string_view key);

    private:
        std::unordered_map<std::string, Object> objects;
        std::unordered_map<std::string, bool> booleans;
        std::unordered_map<std::string, char> characters;
        std::unordered_map<std::string, int> integers;
        std::unordered_map<std::string, long long int> longs;
        std::unordered_map<std::string, float> floats;
        std::unordered_map<std::string, double> doubles;
        std::unordered_map<std::string, std::string> strings;

        bool tokenize(std::string_view data, int &index, std::string stringedType, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var));
        bool tokenizeType(std::string_view data, int &index, std::string &type);
        bool tokenizeKey(std::string_view data, int &index, std::string &key);
        bool tokenizeValue(std::string_view data, int &index, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var));
    };

    std::optional<Object> Load(std::string data);
}