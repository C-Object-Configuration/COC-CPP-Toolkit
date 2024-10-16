#include "coc.hpp"
#include <stdexcept>
#include <limits>

std::optional<coc::Object> coc::Load(std::string data) {
    data.insert(0, " ");
    data.insert(data.length(), " ");
    int index = 0;
    Object object;

    do {
        bool firstCase = false;
        switch (data[index]) {
            default: continue;

            case 'o': {
                int i = index;
                Var var;

                if (!object.tokenize(data, i, "obj", var, [](std::string_view data, int &index, Var &var) {
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
                })) return {};

                index = i;
                std::optional<Object> childObj = coc::Load(var.Value);
                if (!childObj) return {};
                object.objects[var.Key] = std::move(*childObj);
                break;
            }

            case 'b': {
                int i = index;
                Var var;

                if (!object.tokenize(data, i, "bool", var, [](std::string_view data, int &index, Var &var) {
                    bool b = false;
                    switch (data[index++]) {
                        default: return false;
                        case 'f': break;
                        case 't': {
                            b = true;
                            break;
                        }
                    }

                    std::string desiredValue = b ? "rue" : "alse";
                    for (char c : desiredValue) {
                        if (c != data[index++]) return false;
                    }
                    if (data[index] != ' ') return false;

                    var.Value = b ? "1" : "0";
                    return true;
                })) return {};

                index = i;
                object.booleans[var.Key] = (var.Value == "1") ? true : false;
                break;
            }

            case 'c': {
                int i = index;
                Var var;

                if (!object.tokenize(data, i, "char", var, [](std::string_view data, int &index, Var &var) {
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
                object.characters[var.Key] = var.Value[0];
                break;
            }

            case 'i': {
                firstCase = true;
                [[fallthrough]];
            }
            case 'l': {
                int i = index;
                Var var;

                if (!object.tokenize(data, i, (firstCase ? "int" : "long"), var, [](std::string_view data, int &index, Var &var) {
                    if (data[index] == '-') {
                        var.Value += '-';
                        index++;
                    }

                    do {
                        if (data[index] == ' ') break;

                        if (std::isdigit(data[index])) {
                            var.Value += data[index];
                        }
                        else return false;
                    } while (index++ < data.length());

                    return !var.Value.empty();
                })) return {};

                if (firstCase) {
                    try {
                        int i = std::stoi(var.Value);
                        object.integers[var.Key] = i;
                    }
                    catch (const std::out_of_range &e) { return {}; }
                }
                else {
                    try {
                        long long int l = std::stoll(var.Value);
                        object.longs[var.Key] = l;
                    }
                    catch (const std::out_of_range &e) { return {}; }
                }

                index = i;
                break;
            }

            case 'f': {
                firstCase = true;
                [[fallthrough]];
            }
            case 'd': {
                int i = index;
                Var var;

                if (!object.tokenize(data, i, (firstCase ? "float" : "double"), var, [](std::string_view data, int &index, Var &var) {
                    if (data[index] == '-') {
                        var.Value += '-';
                        index++;
                    }

                    bool hasDot = false;
                    do {
                        if (data[index] == ' ') break;

                        if (std::isdigit(data[index])) {
                            var.Value += data[index];
                            continue;
                        }

                        if (data[index] == '.' && !hasDot) {
                            hasDot = true;
                            var.Value += '.';
                            continue;
                        }

                        return false;
                    } while (index++ < data.length());

                    return !var.Value.empty();
                })) return {};

                if (firstCase) {
                    float f;
                    try { f = std::stof(var.Value); }
                    catch (const std::out_of_range &e) { return {}; }

                    if (f == std::numeric_limits<float>::infinity()
                    ||  f == -std::numeric_limits<float>::infinity()
                    ) return {};
                    object.floats[var.Key] = f;
                }
                else {
                    double d;
                    try { d = std::stod(var.Value); }
                    catch (const std::out_of_range &e) { return {}; }

                    if (d == std::numeric_limits<double>::infinity()
                    ||  d == std::numeric_limits<double>::infinity()
                    ) return {};
                    object.doubles[var.Key] = d;
                }

                index = i;
                break;
            }

            case 's': {
                int i = index;
                Var var;

                if (!object.tokenize(data, i, "string", var, [](std::string_view data, int&index, Var &var) {
                    bool opening = false;

                    do {
                        switch (data[index]) {
                            case '"': {
                                if (!opening) {
                                    opening = true;
                                    continue;
                                }

                                if (data[index-1] != '\\') {
                                    return !var.Value.empty();
                                }
                            }

                            default: {
                                if (!opening) return false;
                                var.Value += data[index];
                            }
                        }
                    } while (index++ < data.length());

                    return false;
                })) return {};

                object.strings[var.Key] = var.Value;
                index = i;
                break;
            }
        }
    } while (index++ < data.length());
    return std::move(object);
}