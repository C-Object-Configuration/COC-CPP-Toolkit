#include "etcl.hpp"
#include <stdexcept>

bool etcl::Object::Get(std::string_view key, etcl::Object &outObj) {
    if (!variables.contains(key.data())) return false;
    Var &v = variables.at(key.data());
    if (v.Type != Obj) return false;

    return etcl::Load(v.Value, outObj);
}

bool etcl::Object::Get(std::string_view key, bool &outVar) {
    if (!variables.contains(key.data())) return false;
    Var &v = variables.at(key.data());

    if (v.Type != Bool) return false;
    outVar = (v.Value == "1") ? true : false;
    return true;
}

bool etcl::Object::Get(std::string_view key, long long int &outValue) {
    if (!variables.contains(key.data())) return false;
    Var &v = variables.at(key.data());
    if (v.Type != Int) return false;

    try {
        outValue = std::stoi(v.Value);
        return true;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}