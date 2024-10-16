#include "../src/coc.hpp"
#include <iostream>
#include <format>
#include <limits>
#include <fstream>

template<typename T>
void Print(std::string_view varName, T t, bool spacing = false) {
    std::cout << std::fixed << varName << ": " << t << '\n';
    if (spacing) std::cout << '\n';
}

int main() {
    std::string fileName = "dev/temp/main.coc";

    std::ifstream file;
    file.open(fileName);

    if (file.fail()) {
        std::cout << "Could not open file: " << fileName;
        std::cin.get();
        return 0;
    }

    std::string rawData;
    char tempC;
    while (file.get(tempC)) {
        if (tempC == '\n') tempC = ' ';
        rawData += tempC;
    }

    std::optional<coc::Struct> data = coc::Load(rawData);
    if (!data) {
        std::cout << "Invalid Data!";
        std::cin.get();
        return 0;
    }

    std::optional<coc::Struct> myObject = data->GetStruct("myObject");
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