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

    auto myObject = data->Structs["myObject"];
    if (myObject) {
        auto myChar = myObject->Chars["myChar"];
        auto myBool = myObject->Bools["myBool"];

        if (myChar) Print("myChar", *myChar);
        if (myBool) Print("myBool", *myBool, true);
    }

    auto minInt = data->Ints["minInt"];
    auto maxInt = data->Ints["maxInt"];
    if (minInt) Print("minInt", *minInt);
    if (maxInt) Print("maxInt", *maxInt, true);

    auto minLong = data->Longs["minLong"];
    auto maxLong = data->Longs["maxLong"];
    if (minLong) Print("minLong", *minLong);
    if (maxLong) Print("maxLong", *maxLong, true);

    auto minFloat = data->Floats["minFloat"];
    auto maxFloat = data->Floats["maxFloat"];
    if (minFloat) Print("minFloat", *minFloat);
    if (maxFloat) Print("maxFloat", *maxFloat, true);

    auto minDouble = data->Doubles["minDouble"];
    auto maxDouble = data->Doubles["maxDouble"];
    if (minDouble) Print("minDouble", *minDouble, true);
    if (maxDouble) Print("maxDouble", *maxDouble, true);

    auto myString = data->Strings["myString"];
    if (myString) Print("myString", *myString);

    std::cin.get();
    return 0;
}