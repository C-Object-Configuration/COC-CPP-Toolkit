#include "coc.hpp"

std::optional<coc::Struct> coc::Struct::GetStruct(std::string_view key) {
    if (!structs.contains(key.data())) return {};
    return structs.at(key.data());
}

std::optional<bool> coc::Struct::GetBool(std::string_view key) {
    if (!booleans.contains(key.data())) return {};
    return booleans.at(key.data());
}

std::optional<char> coc::Struct::GetChar(std::string_view key) {
    if (!characters.contains(key.data())) return {};
    return characters.at(key.data());
}

std::optional<int> coc::Struct::GetInt(std::string_view key) {
    if (!integers.contains(key.data())) return {};
    return integers.at(key.data());
}

std::optional<long long int> coc::Struct::GetLong(std::string_view key) {
    if (!longs.contains(key.data())) return {};
    return longs.at(key.data());
}

std::optional<float> coc::Struct::GetFloat(std::string_view key) {
    if (!floats.contains(key.data())) return {};
    return floats.at(key.data());
}

std::optional<double> coc::Struct::GetDouble(std::string_view key) {
    if (!doubles.contains(key.data())) return {};
    return doubles.at(key.data());
}

std::optional<std::string> coc::Struct::GetString(std::string_view key) {
    if (!strings.contains(key.data())) return {};
    return strings.at(key.data());
}