#include "etcl.hpp"

std::optional<etcl::Object> etcl::Object::GetObject(std::string_view key) {
    if (!objects.contains(key.data())) return {};
    return objects.at(key.data());
}

std::optional<bool> etcl::Object::GetBool(std::string_view key) {
    if (!booleans.contains(key.data())) return {};
    return booleans.at(key.data());
}

std::optional<char> etcl::Object::GetChar(std::string_view key) {
    if (!characters.contains(key.data())) return {};
    return characters.at(key.data());
}

std::optional<long long int> etcl::Object::GetInt(std::string_view key) {
    if (!integers.contains(key.data())) return {};
    return integers.at(key.data());
}

std::optional<long double> etcl::Object::GetFloat(std::string_view key) {
    if (!doubles.contains(key.data())) return {};
    return doubles.at(key.data());
}