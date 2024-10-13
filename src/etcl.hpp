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
        std::optional<bool> GetBool(std::string_view key);
        std::optional<char> GetChar(std::string_view key);
        std::optional<long long int> GetInt(std::string_view key);

    private:
        std::unordered_map<std::string, bool> booleans;
        std::unordered_map<std::string, char> characters;
        std::unordered_map<std::string, long long int> integers;

        bool tokenize(std::string_view data, int &index, std::string stringedType, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var));
        bool tokenizeType(std::string_view data, int &index, std::string &type);
        bool tokenizeKey(std::string_view data, int &index, std::string &key);
        bool tokenizeValue(std::string_view data, int &index, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var));
    };

    std::optional<Object> Load(std::string data);
}