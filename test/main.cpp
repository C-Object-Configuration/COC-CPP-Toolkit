#include "../src/etcl.hpp"
#include <iostream>

int main() {
    etcl::Def def("int  num   =    -2147483648            bool   alive=                           false   ");

    int num = 0;
    if (def.Get("num", num)) {
        std::cout << "\nnum: " << num;
    }

    bool alive = false;
    if(def.Get("alive", alive)) {
        std::cout << "\nalive: " << (alive ? "True" : "False");
    }

    std::cin.get();
    return 0;
}