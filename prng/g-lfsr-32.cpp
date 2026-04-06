#include <iostream>
#include <random>
#include <cstdint>


uint32_t g_lfsr_32() {
    static uint32_t reg = 0xf1f1f1f1;
    static constexpr uint8_t fb[17] = {28, 27, 25, 24, 23, 21, 18, 16, 15, 12, 11, 10, 9, 6, 3, 1, 0};

    uint32_t nb = 0;
    for (uint8_t j = 0; j < 17; ++j) { nb ^= reg >> fb[j]; }
    reg = (reg >> 1) | ((nb & 1) << 31);

	return reg;
}

int main() {
    while (true) {
        uint32_t value = g_lfsr_32();
        std::cout.write(reinterpret_cast<const char*>(&value), sizeof(value));
        if (std::cout.bad()) break;
    }
    return 0;
}
