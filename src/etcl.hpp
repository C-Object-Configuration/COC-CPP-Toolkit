#pragma once
#include <string>
#include <string_view>
#include <unordered_map>

namespace etcl {
    enum VarType {
        Null,
        Int,
        Bool
    };

    struct Var {
        VarType Type = Null;
        std::string Key = "";
        std::string Value = "";
        void *Ptr = nullptr;
        void(*Delete)() = nullptr;
    };

    class Def {
    public:
        Def(std::string data);
        ~Def();
        bool Get(std::string key, Var &var);

    private:
        std::unordered_map<std::string_view, Var> pairs;
        bool tokenize(std::string_view data, int &index, std::string stringedType, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var));
        bool tokenizeType(std::string_view data, int &index, std::string &type);
        bool tokenizeKey(std::string_view data, int &index, std::string &key);
        bool tokenizeValue(std::string_view data, int &index, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var));
    };
}