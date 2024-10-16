#include "coc.hpp"

bool coc::Struct::tokenize(std::string_view data, int &index, std::string stringedType, std::string &key, std::string &value, bool(*hasValue)(std::string_view data, int &index, std::string &key, std::string &value)) {
    return tokenizeType(data, index, stringedType) && tokenizeKey(data, index, key) && tokenizeValue(data, index, key, value, hasValue);
}

bool coc::Struct::tokenizeType(std::string_view data, int &index, std::string &type) {
    switch (data[index-1]) {
        default: return false;
        case ' ':
        case '{':
        case '}':
        case '"':
        case '\'':
            break;
    }

    type += ' ';

    for (char c : type) {
        if (c != data[index++]) return false;
    }

    return true;
}

bool coc::Struct::tokenizeKey(std::string_view data, int &index, std::string &key) {
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

bool coc::Struct::tokenizeValue(std::string_view data, int &index, std::string &key, std::string &value, bool(*hasValue)(std::string_view data, int &index, std::string &key, std::string &value)) {
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

    return hasValue(data, index, key, value);
}