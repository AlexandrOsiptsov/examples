#include <iostream>
#include <random>
#include <cstdint>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd()); 

    while (true) {
        uint32_t value = gen();
        std::cout.write(reinterpret_cast<const char*>(&value), sizeof(value));
        if (std::cout.bad()) break;
    }
    return 0;
}
