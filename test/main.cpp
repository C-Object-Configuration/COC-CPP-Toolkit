#include "../src/etcl.hpp"
#include <iostream>

int main() {
    // std::string rawData = "int  num   =    -2147483648      char myChar=    'E'               obj myObject={int age=16}bool   alive=                           false   ";
    std::string rawData = "int  num   =    -2147483648      char myChar=    'E'               bool   alive=                           false   ";
    etcl::Object data;
    if (!etcl::Load(rawData, data)) {
        std::cout << "Data Loading Failed!";
        std::cin.get();
        return 0;
    }

    std::optional<long long int> num = data.GetInt("num");
    if (num) {
        std::cout << "\nnum: " << *num;
    }

    std::optional<char> myChar = data.GetChar("myChar");
    if (myChar) {
        std::cout << "\nmyChar: " << *myChar;
    }

    std::optional<bool> alive = data.GetBool("alive");
    if (alive) {
        std::cout << "\nalive: " << (*alive ? "True" : "False");
    }

    // etcl::Object myObject;
    // if (data.Get("myObject", myObject)) {
    //     long long int age = 0;
    //     if (myObject.Get("age", age)) {
    //         std::cout << "\nmyObject.age: " << age;
    //     }
    // }

    std::cin.get();
    return 0;
}