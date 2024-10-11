#pragma once
#include <string>
#include <unordered_map>

namespace etcl {
    struct Var {
        Var(void(*deletion)(), void *ptr);
        void(*Delete)();
        void *Ptr;
    };

    class Def {
    public:
        Def(std::string data);
        ~Def();
        bool Get(std::string key, Var &var);

    private:
        std::unordered_map<std::string, Var> pairs;
        bool tokenize(std::string &data, int &index, std::string type, std::string &key, std::string &value, bool(*func)(std::string &data, int &index, std::string &value));
        bool tokenizeType(std::string &data, int &index, std::string type);
        bool tokenizeKey(std::string &data, int &index, std::string &key);
        bool tokenizeValue(std::string &data, int &index, std::string &value, bool(*func)(std::string &data, int &index, std::string &value));
    };
}