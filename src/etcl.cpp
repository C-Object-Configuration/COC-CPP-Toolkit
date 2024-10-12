#include "etcl.hpp"
#include <cctype>
#include <iostream>

etcl::Def::Def(std::string data) {
    data.insert(0, " ");
    data.insert(data.length(), " ");
    int index = 0;

    do {
        switch (data[index]) {
            default: continue;

            case 'i': {
                int i = index;
                Var var;

                if (!tokenize(data, i, "int", var, [](std::string_view data, int &index, Var &var) {
                    do {
                        if (data[index] == ' ') break;

                        if (std::isdigit(data[index])) {
                            var.Value += data[index];
                        }
                        else return false;
                    } while (index++ < data.length());
                    return !var.Value.empty();
                })) break;

                var.Type = VarType::Int;
                index = i;
                std::cout << "\nType: " << var.Type << "| Key: " << var.Key << "| Value: " << var.Value << "|\n";
                break;
            }

            case 'b': {
                int i = index;
                Var var;

                if (!tokenize(data, i, "bool", var, [](std::string_view data, int &index, Var &var) {
                    bool b = false;
                    switch (data[index++]) {
                        default: return false;
                        case 'f': break;
                        case 't': {
                            b = true;
                            break;
                        }
                    }

                    std::string desiredValue = b ? "rue " : "alse ";
                    for (char c : desiredValue) {
                        if (c != data[index++]) return false;
                    }

                    var.Value = b ? "true" : "false";
                    return true;
                })) break;

                var.Type = VarType::Bool;
                index = i;
                std::cout << "\nType: " << var.Type << "| Key: " << var.Key << "| Value: " << var.Value << "|\n";
                break;
            }
        }
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

bool etcl::Def::tokenize(std::string_view data, int &index, std::string stringedType, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var)) {
    return tokenizeType(data, index, stringedType) && tokenizeKey(data, index, var.Key) && tokenizeValue(data, index, var, hasValue);
}

bool etcl::Def::tokenizeType(std::string_view data, int &index, std::string &type) {
    if (data[index-1] != ' ') return false;
    type += ' ';

    for (char c : type) {
        if (c != data[index++]) return false;
    }

    return true;
}

bool etcl::Def::tokenizeKey(std::string_view data, int &index, std::string &key) {
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

bool etcl::Def::tokenizeValue(std::string_view data, int &index, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var)) {
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
                goto breakWhile;
            }
        }
    }
    breakWhile:

    return hasValue(data, index, var);
}