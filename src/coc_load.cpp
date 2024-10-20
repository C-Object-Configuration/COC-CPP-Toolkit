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
                std::string key;
                std::vector<std::string> values;

                coc::Struct::tokenizeValueCallback callback = structure.tokenize(data, i, "string", key, values, [](std::string_view data, int&index, bool isArray, std::string &key, std::string &value) {
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
                });

                switch (callback) {
                    case coc::Struct::tokenizeValueCallback::Fail: break;

                    case coc::Struct::tokenizeValueCallback::Single: {
                        structure.Strings.map[key] = values[0];
                        goto breakS;
                    }

                    case coc::Struct::tokenizeValueCallback::Array: {
                        structure.StringArrays.map[key] = std::move(values);
                        goto breakS;
                    }
                }

                i = index;
                key = "";
                values = {};

                callback = structure.tokenize(data, i, "struct", key, values, [](std::string_view data, int &index, bool isArray, std::string &key, std::string &value) {
                    bool begin = false;

                    do {
                        switch (data[index]) {
                            case '{': {
                                begin = true;
                                continue;
                            }

                            case ' ': {
                                if (!begin) continue;
                                [[fallthrough]];
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
                });

                switch (callback) {
                    case coc::Struct::tokenizeValueCallback::Fail: return {};

                    case coc::Struct::tokenizeValueCallback::Single: {
                        std::optional<Struct> childStruct = coc::Load(values[0]);
                        if (!childStruct) return {};
                        structure.Structs.map[key] = std::move(*childStruct);
                        goto breakS;
                    }

                    case coc::Struct::tokenizeValueCallback::Array: {
                        for (std::string &value : values) {
                            auto childStruct = coc::Load(value);
                            if (!childStruct) return {};
                            structure.StructArrays.map[key].emplace_back(std::move(*childStruct));
                        }
                        goto breakS;
                    }
                }

                breakS:
                index = i;
                break;
            }

            case 'b': {
                int i = index;
                std::string key;
                std::vector<std::string> values;

                coc::Struct::tokenizeValueCallback callback = structure.tokenize(data, i, "bool", key, values, [](std::string_view data, int &index, bool isArray, std::string &key, std::string &value) {
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

                    if (data[index] != ' ') {
                        if (!isArray) return false;
                        if (data[index] != ',' && data[index] != ' ' && data[index] != ']') return false;
                    }
                    index--;

                    value = b ? "1" : "0";
                    return true;
                });

                switch (callback) {
                    case coc::Struct::tokenizeValueCallback::Fail: return {};

                    case coc::Struct::tokenizeValueCallback::Single: {
                        structure.Bools.map[key] = (values[0] == "1") ? true : false;
                        goto breakB;
                    }

                    case coc::Struct::tokenizeValueCallback::Array: {
                        for (std::string &value : values) {
                            structure.BoolArrays.map[key].emplace_back((value == "1") ? true : false);
                        }
                        goto breakB;
                    }
                }

                breakB:
                index = i;
                break;
            }

            case 'c': {
                int i = index;
                std::string key;
                std::vector<std::string> values;

                coc::Struct::tokenizeValueCallback callback = structure.tokenize(data, i, "char", key, values, [](std::string_view data, int &index, bool isArray, std::string &key, std::string &value) {
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
                    value += data[index++];
                    return true;
                });

                switch (callback) {
                    case coc::Struct::tokenizeValueCallback::Fail: return {};

                    case coc::Struct::tokenizeValueCallback::Single: {
                        structure.Chars.map[key] = values[0][0];
                        goto breakC;
                    }

                    case coc::Struct::tokenizeValueCallback::Array: {
                        for (std::string &value : values) {
                            structure.CharArrays.map[key].emplace_back(value[0]);
                        }
                        goto breakC;
                    }
                }

                breakC:
                index = i;
                break;
            }

            case 'i': {
                firstCase = true;
                [[fallthrough]];
            }
            case 'l': {
                int i = index;
                std::string key;
                std::vector<std::string> values;

                coc::Struct::tokenizeValueCallback callback = structure.tokenize(data, i, (firstCase ? "int" : "long"), key, values, [](std::string_view data, int &index, bool isArray, std::string &key, std::string &value) {
                    if (data[index] == '-') {
                        value += '-';
                        index++;
                    }

                    do {
                        if (data[index] == ' ') break;
                        if (isArray && (data[index] == ',' || data[index] == ']')) break;

                        if (std::isdigit(data[index])) {
                            value += data[index];
                        }
                        else return false;
                    } while (index++ < data.length());
                    index--;

                    return !value.empty();
                });

                switch (callback) {
                    case coc::Struct::tokenizeValueCallback::Fail: return {};

                    case coc::Struct::tokenizeValueCallback::Single: {
                        if (firstCase) {
                            try {
                                int i = std::stoi(values[0]);
                                structure.Ints.map[key] = i;
                            }
                            catch (const std::out_of_range &e) { return {}; }
                            goto breakI;
                        }

                        try {
                            long long int l = std::stoll(values[0]);
                            structure.Longs.map[key] = l;
                        }
                        catch (const std::out_of_range &e) { return {}; }
                        goto breakI;
                    }

                    case coc::Struct::tokenizeValueCallback::Array: {
                        if (firstCase) {
                            for (std::string &value : values) {
                                try {
                                    int i = std::stoi(value);
                                    structure.IntArrays.map[key].emplace_back(i);
                                }
                                catch (const std::out_of_range &e) { return {}; }
                            }
                            goto breakI;
                        }

                        for (std::string &value : values) {
                            try {
                                long long int l = std::stoll(value);
                                structure.LongArrays.map[key].emplace_back(l);
                            }
                            catch (const std::out_of_range &e) { return {}; }
                        }
                        goto breakI;
                    }
                }

                breakI:
                index = i;
                break;
            }

            case 'f': {
                firstCase = true;
                [[fallthrough]];
            }
            case 'd': {
                int i = index;
                std::string key;
                std::vector<std::string> values;

                coc::Struct::tokenizeValueCallback callback = structure.tokenize(data, i, (firstCase ? "float" : "double"), key, values, [](std::string_view data, int &index, bool isArray, std::string &key, std::string &value) {
                    if (data[index] == '-') {
                        value += '-';
                        index++;
                    }

                    bool hasDot = false;
                    do {
                        if (data[index] == ' ') break;
                        if (isArray && (data[index] == ',' || data[index] == ']')) break;

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
                    index--;

                    return !value.empty();
                });

                switch (callback) {
                    case coc::Struct::tokenizeValueCallback::Fail: return {};

                    case coc::Struct::tokenizeValueCallback::Single: {
                        if (firstCase) {
                            float f;
                            try { f = std::stof(values[0]); }
                            catch (const std::out_of_range &e) { return {}; }

                            if (f == std::numeric_limits<float>::infinity()
                            ||  f == -std::numeric_limits<float>::infinity()
                            ) return {};
                            structure.Floats.map[key] = f;
                            goto breakD;
                        }

                        double d;
                        try { d = std::stod(values[0]); }
                        catch (const std::out_of_range &e) { return {}; }

                        if (d == std::numeric_limits<double>::infinity()
                        ||  d == std::numeric_limits<double>::infinity()
                        ) return {};
                        structure.Doubles.map[key] = d;
                        goto breakD;
                    }

                    case coc::Struct::tokenizeValueCallback::Array: {
                        if (firstCase) {
                            for (std::string &value : values) {
                                float f;
                                try { f = std::stof(value); }
                                catch (const std::out_of_range &e) { return {}; }

                                if (f == std::numeric_limits<float>::infinity()
                                ||  f == -std::numeric_limits<float>::infinity()
                                ) return {};
                                structure.FloatArrays.map[key].emplace_back(f);
                            }
                            goto breakD;
                        }

                        for (std::string &value : values) {
                            double d;
                            try { d = std::stod(value); }
                            catch (const std::out_of_range &e) { return {}; }

                            if (d == std::numeric_limits<double>::infinity()
                            ||  d == std::numeric_limits<double>::infinity()
                            ) return {};
                            structure.DoubleArrays.map[key].emplace_back(d);
                        }
                        goto breakD;
                    }
                }

                breakD:
                index = i;
                break;
            }
        }
    } while (index++ < data.length());
    return std::move(structure);
}