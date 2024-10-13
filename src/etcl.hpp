#pragma once
#include <string>
#include <string_view>
#include <unordered_map>

namespace etcl {
    enum VarType {
        Null,
        Obj,
        Int,
        Bool
    };

    struct Var {
        VarType Type = Null;
        std::string Key = "";
        std::string Value = "";
    };

    class Object {
    friend bool Load(std::string data, Object &outObj);
    public:
        bool Get(std::string_view key, Object &outObj);
        bool Get(std::string_view key, bool &outValue);
        bool Get(std::string_view key, long long int &outValue);

    private:
        std::unordered_map<std::string, Var> variables;
        bool tokenize(std::string_view data, int &index, std::string stringedType, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var));
        bool tokenizeType(std::string_view data, int &index, std::string &type);
        bool tokenizeKey(std::string_view data, int &index, std::string &key);
        bool tokenizeValue(std::string_view data, int &index, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var));
    };

    bool Load(std::string data, Object &outObj);
}