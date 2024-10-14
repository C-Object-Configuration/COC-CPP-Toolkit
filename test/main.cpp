#include "../src/etcl.hpp"
#include <iostream>
#include <format>
#include <limits>

template<typename T>
void Print(std::string_view varName, T t, bool spacing = false) {
    std::cout << std::fixed << varName << ": " << t << '\n';
    if (spacing) std::cout << '\n';
}

int main() {
    std::string rawData = "obj myObject = {char myChar='E'bool myBool = true}";
    rawData += std::format(" int minInt = {}", std::to_string(-std::numeric_limits<int>::max()));
    rawData += std::format(" int maxInt = {}", std::to_string(std::numeric_limits<int>::max()));
    rawData += std::format(" long minLong = {}", std::to_string(-std::numeric_limits<long long int>::max()));
    rawData += std::format(" long maxLong = {}", std::to_string(std::numeric_limits<long long int>::max()));
    rawData += std::format(" float minFloat = {}", std::to_string(-std::numeric_limits<float>::max()));
    rawData += std::format(" float maxFloat = {}", std::to_string(std::numeric_limits<float>::max()));
    rawData += std::format(" double minDouble = {}", std::to_string(-std::numeric_limits<double>::max()));
    rawData += std::format(" double maxDouble = {}", std::to_string(std::numeric_limits<double>::max()));
    rawData += std::format(" string myString = {}", "\"abc123\"");

    std::optional<etcl::Object> data = etcl::Load(rawData);
    if (!data) {
        std::cout << "Invalid Data!";
        std::cin.get();
        return 0;
    }

    std::optional<etcl::Object> myObject = data->GetObject("myObject");
    if (myObject) {
        std::optional<char> myChar = myObject->GetChar("myChar");
        std::optional<bool> myBool = myObject->GetBool("myBool");

        if (myChar) Print("myChar", *myChar);
        if (myBool) Print("myBool", *myBool, true);
    }

    std::optional<int> minInt = data->GetInt("minInt");
    std::optional<int> maxInt = data->GetInt("maxInt");
    if (minInt) Print("minInt", *minInt);
    if (maxInt) Print("maxInt", *maxInt, true);

    std::optional<long long int> minLong = data->GetLong("minLong");
    std::optional<long long int> maxLong = data->GetLong("maxLong");
    if (minLong) Print("minLong", *minLong);
    if (maxLong) Print("maxLong", *maxLong, true);

    std::optional<float> minFloat = data->GetFloat("minFloat");
    std::optional<float> maxFloat = data->GetFloat("maxFloat");
    if (minFloat) Print("minFloat", *minFloat);
    if (maxFloat) Print("maxFloat", *maxFloat, true);

    std::optional<double> minDouble = data->GetDouble("minDouble");
    std::optional<double> maxDouble = data->GetDouble("maxDouble");
    if (minDouble) Print("minDouble", *minDouble, true);
    if (maxDouble) Print("maxDouble", *maxDouble, true);

    std::optional<std::string> myString = data->GetString("myString");
    if (myString) Print("myString", *myString);

    std::cin.get();
    return 0;
}