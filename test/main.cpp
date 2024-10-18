#include "../src/coc.hpp"
#include <iostream>

int main() {
    auto data = coc::Open("main.coc");
    if (!data) {
        std::cout << "Invalid Data!\n" << "Enter to continue";
        std::cin.get();
        return 0;
    }

    auto myObject = data->Structs["myObject"];
    if (myObject) {
        auto myChar = myObject->Chars["myChar"];
        auto myBool = myObject->Bools["myBool"];
        auto myString = data->Strings["myString"];

        if (myChar) std::cout << "\nmyChar: " << *myChar;
        if (myBool) std::cout << "\nmyBool: " << *myBool;
        if (myString) std::cout << "\nmyString: " << *myString;
    }

    auto minInt = data->Ints["minInt"];
    auto maxInt = data->Ints["maxInt"];
    if (minInt) std::cout << "\nminInt: " << *minInt;
    if (maxInt) std::cout << "\nmaxInt: " << *maxInt;

    auto minLong = data->Longs["minLong"];
    auto maxLong = data->Longs["maxLong"];
    if (minLong) std::cout << "\nminLong: " << *minLong;
    if (maxLong) std::cout << "\nmaxLong: " << *maxLong;

    auto minFloat = data->Floats["minFloat"];
    auto maxFloat = data->Floats["maxFloat"];
    if (minFloat) std::cout << "\nminFloat: " << *minFloat;
    if (maxFloat) std::cout << "\nmaxFloat: " << *maxFloat;

    auto minDouble = data->Doubles["minDouble"];
    auto maxDouble = data->Doubles["maxDouble"];
    if (minDouble) std::cout << "\nminDouble: " << *minDouble;
    if (maxDouble) std::cout << "\nmaxDouble: " << *maxDouble;

    std::cout << "\n\nEnter to continue";
    std::cin.get();
    return 0;
}