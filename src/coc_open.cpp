#include "coc.hpp"
#include <fstream>

std::optional<coc::Struct> coc::Open(std::string path) {
    std::ifstream file;
    file.open(path);
    if (file.fail()) return {};

    std::string data;
    char c;
    while (file.get(c)) {
        if (c == '\n') c = ' ';
        data += c;
    }

    std::optional<coc::Struct> structure = coc::Load(data);
    return structure
        ? std::move(structure)
        : std::nullopt
    ;
}