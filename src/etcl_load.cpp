#include "etcl.hpp"
#include <stdexcept>

std::optional<etcl::Object> etcl::Load(std::string data) {
    data.insert(0, " ");
    data.insert(data.length(), " ");
    int index = 0;
    Object outObj;

    do {
        switch (data[index]) {
            default: continue;

            // case 'o': {
            //     int i = index;
            //     Var var;

            //     if (!outObj.tokenize(data, i, "obj", var, [](std::string_view data, int &index, Var &var) {
            //         bool begin = false;

            //         do {
            //             switch (data[index]) {
            //                 case '{': {
            //                     begin = true;
            //                     continue;
            //                 }

            //                 case ' ': {
            //                     if (!begin) continue;
            //                 }

            //                 default: {
            //                     if (!begin) return false;
            //                     var.Value += data[index];
            //                     continue;
            //                 }

            //                 case '}': return begin;
            //             }
            //         } while (index++ < data.length());
            //         return false;
            //     })) return false;

            //     index = i;
            //     var.Type = VarType::Obj;
            //     outObj.variables[var.Key] = std::move(var);
            //     break;
            // }

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
                })) return {};

                index = i;
                outObj.booleans[var.Key] = (var.Value == "1") ? true : false;
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
                })) return {};

                index = i;
                outObj.characters[var.Key] = var.Value[0];
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
                })) return {};

                index = i;
                try {
                    int i = std::stoi(var.Value);
                    outObj.integers[var.Key] = i;
                }
                catch (const std::out_of_range &e) {
                    return {};
                }
                break;
            }
        }
    } while (index++ < data.length());
    return std::move(outObj);
}