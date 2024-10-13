#include "etcl.hpp"

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

// bool etcl::Object::Get(std::string_view key, etcl::Object &outObj) {
//     if (!variables.contains(key.data())) return false;
//     Var &v = variables.at(key.data());
//     if (v.Type != VarType::Obj) return false;

//     return etcl::Load(v.Value, outObj);
// }