#include "../src/etcl.hpp"
#include <iostream>

int main() {
    // std::string rawData = "int  num   =    -2147483648      char myChar=    'E'               obj myObject={int age=16}bool   alive=                           false   ";
    std::optional<etcl::Object> data = etcl::Load("int  num   =    -2147483648      char myChar=    'E'               bool   alive=                           false   ");
    if (!data) {
        std::cout << "Invalid Data!";
        std::cin.get();
        return 0;
    }

    std::optional<long long int> num = data->GetInt("num");
    if (num) {
        std::cout << "\nnum: " << *num;
    }

    std::optional<char> myChar = data->GetChar("myChar");
    if (myChar) {
        std::cout << "\nmyChar: " << *myChar;
    }

    std::optional<bool> alive = data->GetBool("alive");
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