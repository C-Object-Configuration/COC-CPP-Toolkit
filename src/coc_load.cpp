#include "coc.hpp"
#include <stdexcept>
#include <limits>

std::optional<coc::Struct> coc::Load(std::string data) {
    data.insert(0, " ");
    data.insert(data.length(), " ");
    int index = 0;
    Struct structure;

    do {
        bool firstCase = false;
        switch (data[index]) {
            default: continue;

            case 's': {
                int i = index;
                std::string key, value = "";

                if (structure.tokenize(data, i, "string", key, value, [](std::string_view data, int&index, std::string &key, std::string &value) {
                    bool opening = false;

                    do {
                        switch (data[index]) {
                            case '"': {
                                if (!opening) {
                                    opening = true;
                                    continue;
                                }

                                if (data[index-1] != '\\') {
                                    return !value.empty();
                                }
                            }

                            default: {
                                if (!opening) return false;
                                value += data[index];
                            }
                        }
                    } while (index++ < data.length());

                    return false;
                })) {
                    structure.Strings.map[key] = value;
                    index = i;
                    break;
                }

                i = index;
                key = "";
                value = "";

                if (structure.tokenize(data, i, "struct", key, value, [](std::string_view data, int &index, std::string &key, std::string &value) {
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
                                value += data[index];
                                continue;
                            }

                            case '}': return begin;
                        }
                    } while (index++ < data.length());
                    return false;
                })) {
                    index = i;
                    std::optional<Struct> childStruct = coc::Load(value);
                    if (!childStruct) return {};
                    structure.Structs.map[key] = std::move(*childStruct);
                    break;
                };
            }

            case 'b': {
                int i = index;
                std::string key, value = "";

                if (!structure.tokenize(data, i, "bool", key, value, [](std::string_view data, int &index, std::string &key, std::string &value) {
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

                    value = b ? "1" : "0";
                    return true;
                })) return {};

                index = i;
                structure.Bools.map[key] = (value == "1") ? true : false;
                break;
            }

            case 'c': {
                int i = index;
                std::string key, value = "";

                if (!structure.tokenize(data, i, "char", key, value, [](std::string_view data, int &index, std::string &key, std::string &value) {
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
                    value += data[index];
                    return true;
                })) return {};

                index = i;
                structure.Chars.map[key] = value[0];
                break;
            }

            case 'i': {
                firstCase = true;
                [[fallthrough]];
            }
            case 'l': {
                int i = index;
                std::string key, value = "";

                if (!structure.tokenize(data, i, (firstCase ? "int" : "long"), key, value, [](std::string_view data, int &index, std::string &key, std::string &value) {
                    if (data[index] == '-') {
                        value += '-';
                        index++;
                    }

                    do {
                        if (data[index] == ' ') break;

                        if (std::isdigit(data[index])) {
                            value += data[index];
                        }
                        else return false;
                    } while (index++ < data.length());

                    return !value.empty();
                })) return {};

                if (firstCase) {
                    try {
                        int i = std::stoi(value);
                        structure.Ints.map[key] = i;
                    }
                    catch (const std::out_of_range &e) { return {}; }
                }
                else {
                    try {
                        long long int l = std::stoll(value);
                        structure.Longs.map[key] = l;
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
                std::string key, value = "";

                if (!structure.tokenize(data, i, (firstCase ? "float" : "double"), key, value, [](std::string_view data, int &index, std::string &key, std::string &value) {
                    if (data[index] == '-') {
                        value += '-';
                        index++;
                    }

                    bool hasDot = false;
                    do {
                        if (data[index] == ' ') break;

                        if (std::isdigit(data[index])) {
                            value += data[index];
                            continue;
                        }

                        if (data[index] == '.' && !hasDot) {
                            hasDot = true;
                            value += '.';
                            continue;
                        }

                        return false;
                    } while (index++ < data.length());

                    return !value.empty();
                })) return {};

                if (firstCase) {
                    float f;
                    try { f = std::stof(value); }
                    catch (const std::out_of_range &e) { return {}; }

                    if (f == std::numeric_limits<float>::infinity()
                    ||  f == -std::numeric_limits<float>::infinity()
                    ) return {};
                    structure.Floats.map[key] = f;
                }
                else {
                    double d;
                    try { d = std::stod(value); }
                    catch (const std::out_of_range &e) { return {}; }

                    if (d == std::numeric_limits<double>::infinity()
                    ||  d == std::numeric_limits<double>::infinity()
                    ) return {};
                    structure.Doubles.map[key] = d;
                }

                index = i;
                break;
            }
        }
    } while (index++ < data.length());
    return std::move(structure);
}