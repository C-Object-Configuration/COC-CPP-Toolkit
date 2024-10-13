#include "etcl.hpp"

bool etcl::Load(std::string data, Object &outObj) {
    data.insert(0, " ");
    data.insert(data.length(), " ");
    int index = 0;

    do {
        switch (data[index]) {
            default: continue;

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
                                continue;
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

            case 'c': {
                int i = index;
                Var var;

                if (!outObj.tokenize(data, i, "char", var, [](std::string_view data, int &index, Var &var) {
                    bool begin = false;

                    do {
                        if (data[index] == ' ') continue;
                        if (data[index] != '\'') return false;
                        begin = true;
                        break;
                    } while (index++ < data.length());

                    if (!begin) return false;
                    index++;

                    if (data[index+1] != '\'') return false;
                    var.Value += data[index];
                    return true;
                })) return false;

                index = i;
                var.Type = VarType::Char;
                outObj.variables[var.Key] = std::move(var);
                break;
            }

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
                var.Type = VarType::Int;
                outObj.variables[var.Key] = std::move(var);
                break;
            }
        }
    } while (index++ < data.length());
    return true;
}