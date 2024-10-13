#include "etcl.hpp"
#include <cctype>

bool etcl::Object::tokenize(std::string_view data, int &index, std::string stringedType, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var)) {
    return tokenizeType(data, index, stringedType) && tokenizeKey(data, index, var.Key) && tokenizeValue(data, index, var, hasValue);
}

bool etcl::Object::tokenizeType(std::string_view data, int &index, std::string &type) {
    switch (data[index-1]) {
        default: return false;

        case ' ':
        case '{':
        case '}': break;
    }

    type += ' ';

    for (char c : type) {
        if (c != data[index++]) return false;
    }

    return true;
}

bool etcl::Object::tokenizeKey(std::string_view data, int &index, std::string &key) {
    do {
        if (data[index] == ' ') {
            if (!key.empty()) return true;
            continue;
        }

        if (data[index] == '=' && !key.empty()) {
            index--;
            return true;
        }

        key += data[index];
    } while (index++ < data.length());
    return false;
}

bool etcl::Object::tokenizeValue(std::string_view data, int &index, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var)) {
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

bool etcl::Load(std::string data, Object &outObj) {
    data.insert(0, " ");
    data.insert(data.length(), " ");
    int index = 0;

    do {
        switch (data[index]) {
            default: continue;

            case 'i': {
                int i = index;
                Var var;

                if (!outObj.tokenize(data, i, "int", var, [](std::string_view data, int &index, Var &var) {
                    do {
                        if (data[index] == ' ') break;

                        if (std::isdigit(data[index]) || data[index] == '-') {
                            var.Value += data[index];
                        }
                        else return false;
                    } while (index++ < data.length());
                    return !var.Value.empty();
                })) return false;

                index = i;
                var.Type = Int;
                outObj.variables[var.Key] = std::move(var);
                break;
            }

            case 'b': {
                int i = index;
                Var var;

                if (!outObj.tokenize(data, i, "bool", var, [](std::string_view data, int &index, Var &var) {
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

                    var.Value = b ? "1" : "0";
                    return true;
                })) return false;

                index = i;
                var.Type = VarType::Bool;
                outObj.variables[var.Key] = std::move(var);
                break;
            }

            case 'o': {
                int i = index;
                Var var;

                if (!outObj.tokenize(data, i, "obj", var, [](std::string_view data, int &index, Var &var) {
                    bool begin = false;

                    do {
                        switch (data[index]) {
                            case '{': {
                                begin = true;
                                continue;
                            }

                            case ' ': {
                                if (!begin) continue;
                            }

                            default: {
                                if (!begin) return false;
                                var.Value += data[index];
                                break;
                            }

                            case '}': return begin;
                        }
                    } while (index++ < data.length());
                    return false;
                })) return false;

                index = i;
                var.Type = VarType::Obj;
                outObj.variables[var.Key] = std::move(var);
                break;
            }
        }
    } while (index++ < data.length());
    return true;
}