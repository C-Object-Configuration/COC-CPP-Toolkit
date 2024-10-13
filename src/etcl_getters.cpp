#include "etcl.hpp"
#include <stdexcept>
#include <iostream>

bool etcl::Object::Get(std::string_view key, etcl::Object &outObj) {
    if (!variables.contains(key.data())) return false;
    Var &v = variables.at(key.data());
    if (v.Type != VarType::Obj) return false;

    return etcl::Load(v.Value, outObj);
}

bool etcl::Object::Get(std::string_view key, bool &outBool) {
    if (!variables.contains(key.data())) return false;
    Var &v = variables.at(key.data());

    if (v.Type != VarType::Bool) return false;
    outBool = (v.Value == "1") ? true : false;
    return true;
}

bool etcl::Object::Get(std::string_view key, char &outChar) {
    if (!variables.contains(key.data())) return false;
    Var &v = variables.at(key.data());

    if (v.Type != VarType::Char) return false;
    outChar = v.Value[0];
    return true;
}

bool etcl::Object::Get(std::string_view key, long long int &outInt) {
    if (!variables.contains(key.data())) return false;
    Var &v = variables.at(key.data());
    if (v.Type != VarType::Int) return false;

    try {
        outInt = std::stoi(v.Value);
        return true;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}