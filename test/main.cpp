#include "../src/etcl.hpp"
#include <iostream>

int main() {
    std::string rawData = "int  num   =    -2147483648         obj myObject={int age=16}bool   alive=                           false   ";
    etcl::Object data;
    if (!etcl::Load(rawData, data)) return 0;

    long long int num = 0;
    if (data.Get("num", num)) {
        std::cout << "\nnum: " << num;
    }

    etcl::Object myObject;
    if (data.Get("myObject", myObject)) {
        long long int age = 0;
        if (myObject.Get("age", age)) {
            std::cout << "\nmyObject.age: " << age;
        }
    }

    bool alive = false;
    if(data.Get("alive", alive)) {
        std::cout << "\nalive: " << (alive ? "True" : "False");
    }

    std::cin.get();
    return 0;
}