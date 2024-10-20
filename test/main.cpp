#include "../src/coc.hpp"
#include <iostream>
#include <vector>

void People(std::vector<coc::Struct> &people) {
    std::cout << "\n\n-People-";

    for (coc::Struct &person : people) {
        auto name = person.Strings["Name"];
        auto foods = person.StringArrays["Foods"];

        if (name) std::cout << '\n' << *name << " Foods:";
        if (foods) {
            for (std::string &s : *foods) {
                std::cout << "\n  " << s;
            }
        }
    }
}

void Chars(coc::Struct &object) {
    std::cout << "\n\n-Chars-";

    auto myChar = object.Chars["MyChar"];
    auto array = object.CharArrays["Array"];

    if (myChar) std::cout << "\nMyChar: " << *myChar;
    if (array) {
        for (int i = 0; i < (*array).size(); i++) {
            std::cout << "\nArray[" << i << "]: " << (*array)[i];
        }
    }
}

void Bools(coc::Struct &object) {
    std::cout << "\n\n-Bools-";

    auto myBool = object.Bools["MyBool"];
    auto array = object.BoolArrays["Array"];

    if (myBool) std::cout << "\nMyBool: " << *myBool;
    if (array) {
        for (int i = 0; i < (*array).size(); i++) {
            std::cout << "\nArray[" << i << "]: " << (*array)[i];
        }
    }
}

#define PRINT_NUMBER(type, arrayType)                               \
void type(coc::Struct &object, std::string_view typeName) {         \
    std::cout << "\n\n-" << typeName << '-';                        \
                                                                    \
    auto min = object.type["Min"];                                  \
    auto max = object.type["Max"];                                  \
    auto array = object.arrayType["Array"];                         \
                                                                    \
    if (min) std::cout << "\nMin: " << *min;                        \
    if (max) std::cout << "\nMax: " << *max;                        \
    if (array) {                                                    \
        for (int i = 0; i < (*array).size(); i++) {                 \
            std::cout << "\nArray[" << i << "]: " << (*array)[i];   \
        }                                                           \
    }                                                               \
}

PRINT_NUMBER(Ints, IntArrays)
PRINT_NUMBER(Longs, LongArrays)
PRINT_NUMBER(Floats, FloatArrays)
PRINT_NUMBER(Doubles, DoubleArrays)

int main() {
    auto data = coc::Open("main.coc");
    if (!data) {
        std::cout << "Invalid Data!\n" << "Enter to continue";
        std::cin.get();
        return 0;
    }

    auto people = data->StructArrays["People"];
    if (people) People(*people);

    auto chars = data->Structs["Chars"];
    if (chars) Chars(*chars);

    auto bools = data->Structs["Bools"];
    if (bools) Bools(*bools);

    auto numbers = data->Structs["Numbers"];
    if (numbers) {
        auto ints = numbers->Structs["Ints"];
        if (ints) Ints(*ints, "Ints");

        auto longs = numbers->Structs["Longs"];
        if (longs) Longs(*longs, "Longs");

        auto floats = numbers->Structs["Floats"];
        if (floats) Floats(*floats, "Floats");

        auto doubles = numbers->Structs["Doubles"];
        if (doubles) Doubles(*doubles, "Doubles");
    }

    std::cout << "\n\nEnter to continue";
    std::cin.get();
    return 0;
}