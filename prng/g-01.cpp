#include <iostream>
#include <random>
#include <cstdint>


uint32_t g01() {
    static bool f;
    f = !f;
    return f ? 1 : 0;
}

int main() {
    while (true) {
        uint32_t value = g01();
        std::cout.write(reinterpret_cast<const char*>(&value), sizeof(value));
        if (std::cout.bad()) break;
    }
    return 0;
}
