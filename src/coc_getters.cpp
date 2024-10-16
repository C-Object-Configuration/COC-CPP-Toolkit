#include "coc.hpp"

std::optional<coc::Object> coc::Object::GetObject(std::string_view key) {
    if (!objects.contains(key.data())) return {};
    return objects.at(key.data());
}

std::optional<bool> coc::Object::GetBool(std::string_view key) {
    if (!booleans.contains(key.data())) return {};
    return booleans.at(key.data());
}

std::optional<char> coc::Object::GetChar(std::string_view key) {
    if (!characters.contains(key.data())) return {};
    return characters.at(key.data());
}

std::optional<int> coc::Object::GetInt(std::string_view key) {
    if (!integers.contains(key.data())) return {};
    return integers.at(key.data());
}

std::optional<long long int> coc::Object::GetLong(std::string_view key) {
    if (!longs.contains(key.data())) return {};
    return longs.at(key.data());
}

std::optional<float> coc::Object::GetFloat(std::string_view key) {
    if (!floats.contains(key.data())) return {};
    return floats.at(key.data());
}

std::optional<double> coc::Object::GetDouble(std::string_view key) {
    if (!doubles.contains(key.data())) return {};
    return doubles.at(key.data());
}

std::optional<std::string> coc::Object::GetString(std::string_view key) {
    if (!strings.contains(key.data())) return {};
    return strings.at(key.data());
}