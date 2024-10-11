#include "etcl.hpp"
#include <cctype>
#include <iostream>

etcl::Var::Var(void(*deletion)(), void *ptr)
    : Delete(deletion), Ptr(ptr) {}

etcl::Def::Def(std::string data) {
    data.insert(0, " ");
    int index = 0;

    std::string key, value = "";

    do {
        switch (data[index]) {
            default: continue;

            case 'i': {
                int i = index;

                if (!tokenize(data, i, "int", key, value, [](std::string &data, int &index, std::string &value) {
                    while (index++ < data.length()) {
                        if (data[index] == ' ') break;

                        if (std::isdigit(data[index])) {
                            value += data[index];
                        }
                        else return false;
                    }
                    return !value.empty();
                })) break;

                index = i;
                break;
            }

            case 'b': {
                int i = index;

                if (!tokenize(data, i, "bool", key, value, [](std::string &data, int &index, std::string &value) {
                    std::string desiredValue = " false ";

                    for (char c : desiredValue) {
                        if (c != data[index++]) return false;
                    }

                    value = "false";
                    return !value.empty();
                })) break;

                index = i;
                break;
            }
        }
        std::cout
            << "\n Key: |" << key << '|'
            << "\n Value: |" << value << '|'
            << "\n\n"
        ;
        key = "";
        value = "";
    } while (index++ < data.length());
}

etcl::Def::~Def() {
    for (auto &[key, var] : pairs) {
        var.Delete();
    }
}

bool etcl::Def::Get(std::string key, Var &var) {
    if (!pairs.contains(key)) return false;
    var = pairs.at(key);
    return true;
}

bool etcl::Def::tokenize(std::string &data, int &index, std::string type, std::string &key, std::string &value, bool(*func)(std::string &data, int &index, std::string &value)) {
    return tokenizeType(data, index, type) && tokenizeKey(data, index, key) && tokenizeValue(data, index, value, func);
}

bool etcl::Def::tokenizeType(std::string &data, int &index, std::string type) {
    if (data[index-1] != ' ') return false;
    type += ' ';

    for (char c : type) {
        if (c != data[index++]) return false;
    }

    return true;
}

bool etcl::Def::tokenizeKey(std::string &data, int &index, std::string &key) {
    while (index++ < data.length()) {
        if (data[index] == ' ') {
            if (!key.empty()) return true;
            continue;
        }

        if (data[index] == '=' && !key.empty()) {
            index--;
            return true;
        }

        key += data[index];
    }
    return false;
}

bool etcl::Def::tokenizeValue(std::string &data, int &index, std::string &value, bool(*func)(std::string &data, int &index, std::string &value)) {
    bool hasEqual = false;

    while (index++ < data.length()) {
        switch (data[index]) {
            case ' ': continue;

            case '=': {
                if (hasEqual) return false;
                hasEqual = true;
                break;
            }

            default: {
                if (!hasEqual) return false;
                index--;
                goto breakWhile;
            }
        }
    }
    breakWhile:

    return func(data, index, value);
}