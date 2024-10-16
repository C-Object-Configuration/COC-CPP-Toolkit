#include "coc.hpp"

bool coc::Object::tokenize(std::string_view data, int &index, std::string stringedType, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var)) {
    return tokenizeType(data, index, stringedType) && tokenizeKey(data, index, var.Key) && tokenizeValue(data, index, var, hasValue);
}

bool coc::Object::tokenizeType(std::string_view data, int &index, std::string &type) {
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

bool coc::Object::tokenizeKey(std::string_view data, int &index, std::string &key) {
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

bool coc::Object::tokenizeValue(std::string_view data, int &index, Var &var, bool(*hasValue)(std::string_view data, int &index, Var &var)) {
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