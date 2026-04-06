#include <iostream>
#include <random>
#include <cstdint>


uint32_t g_lfsr_32() {
    static uint8_t reg = 0xf1;
    static constexpr uint8_t fb[4] = {0, 2, 3, 4};

    uint32_t res = 0;
    for (uint8_t i = 0; i < 4; ++i){
        uint8_t nb = 0;
	    for (uint8_t j = 0; j < 4; ++j) { nb ^= reg >> fb[j]; }

        res |= (reg << ((3 - i) * 8));
        reg = (reg >> 1) | ((nb & 1) << 7);
    }
	return res;
}

int main() {
    while (true) {
        uint32_t value = g_lfsr_32();
        std::cout.write(reinterpret_cast<const char*>(&value), sizeof(value));
        if (std::cout.bad()) break;
    }
    return 0;
}
