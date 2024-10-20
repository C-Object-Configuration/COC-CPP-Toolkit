#include "../src/coc.hpp"
#include <iostream>

void Globals(coc::Struct &object) {
    std::cout << "\n\n-Globals-";

    auto myString = object.Strings["MyString"];
    auto array = object.StringArrays["Array"];

    if (myString) std::cout << "\nMyString: " << *myString;
    if (array) {
        int count = 0;
        for (std::string &s : *array) {
            std::cout << "\nArray[" << count++ << "]: " << s;
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

void Ints(coc::Struct &object) {
    std::cout << "\n\n-Ints-";

    auto min = object.Ints["Min"];
    auto max = object.Ints["Max"];
    auto array = object.IntArrays["Array"];

    if (min) std::cout << "\nMin: " << *min;
    if (max) std::cout << "\nMax: " << *max;
    if (array) {
        for (int i = 0; i < (*array).size(); i++) {
            std::cout << "\nArray[" << i << "]: " << (*array)[i];
        }
    }
}

void Longs(coc::Struct &object) {
    std::cout << "\n\n-Longs-";

    auto min = object.Longs["Min"];
    auto max = object.Longs["Max"];
    auto array = object.LongArrays["Array"];

    if (min) std::cout << "\nMin: " << *min;
    if (max) std::cout << "\nMax: " << *max;
    if (array) {
        for (int i = 0; i < (*array).size(); i++) {
            std::cout << "\nArray[" << i << "]: " << (*array)[i];
        }
    }
}

void Floats(coc::Struct &object) {
    std::cout << "\n\n-Floats-";

    auto min = object.Floats["Min"];
    auto max = object.Floats["Max"];
    auto array = object.FloatArrays["Array"];

    if (min) std::cout << "\nMin: " << *min;
    if (max) std::cout << "\nMax: " << *max;
    if (array) {
        for (int i = 0; i < (*array).size(); i++) {
            std::cout << "\nArray[" << i << "]: " << (*array)[i];
        }
    }
}

void Doubles(coc::Struct &object) {
    std::cout << "\n\n-Doubles-";

    auto min = object.Doubles["Min"];
    auto max = object.Doubles["Max"];
    auto array = object.DoubleArrays["Array"];

    if (min) std::cout << "\nMin: " << *min;
    if (max) std::cout << "\nMax: " << *max;
    if (array) {
        for (int i = 0; i < (*array).size(); i++) {
            std::cout << "\nArray[" << i << "]: " << (*array)[i];
        }
    }
}

int main() {
    auto data = coc::Open("main.coc");
    if (!data) {
        std::cout << "Invalid Data!\n" << "Enter to continue";
        std::cin.get();
        return 0;
    }
#define Debug
#ifdef Debug
    Globals(*data);

    auto chars = data->Structs["Chars"];
    if (chars) Chars(*chars);

    auto bools = data->Structs["Bools"];
    if (bools) Bools(*bools);

    auto ints = data->Structs["Ints"];
    if (ints) Ints(*ints);

    auto longs = data->Structs["Longs"];
    if (longs) Longs(*longs);

    auto floats = data->Structs["Floats"];
    if (floats) Floats(*floats);

    auto doubles = data->Structs["Doubles"];
    if (doubles) Doubles(*doubles);
#endif

    std::cout << "\n\nEnter to continue";
    std::cin.get();
    return 0;
}