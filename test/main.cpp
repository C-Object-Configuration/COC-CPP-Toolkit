#include "../src/etcl.hpp"
#include <iostream>

int main() {
    std::string rawData = "int  num   =    -2147483648            bool   alive=                           false   ";
    etcl::Obj data;
    if (!etcl::Load(rawData, data)) return 0;

    int num = 0;
    if (data.Get("num", num)) {
        std::cout << "\nnum: " << num;
    }

    bool alive = false;
    if(data.Get("alive", alive)) {
        std::cout << "\nalive: " << (alive ? "True" : "False");
    }

    std::cin.get();
    return 0;
}