#include <iostream>
#include <cstdint>
#include <iomanip>
#include <unordered_set>
#include <functional>
#include <vector>
#include <unordered_map>
#include <numeric>

void printbits(uint8_t n) {
	for (uint8_t i = 0; i < 8; ++i) {
		std::cout << ((n >> (7 - i)) & 1) << " ";
	}
}

void printnibbles(uint8_t n) {
	std::cout << std::setfill('0') << std::setw(4) << std::hex << n;
}

uint8_t lfsr_shift(const uint8_t reg, const uint8_t* fb, const size_t fb_size) {
	uint8_t nb = 0;
	for (uint8_t j = 0; j < fb_size; ++j) { nb ^= reg >> fb[j]; }
	return (reg >> 1) | ((nb & 1) << 7);
}

uint8_t nfsr_shift(const uint8_t reg, const uint8_t* fb, const size_t fb_size) {
	uint8_t nb = 0;
	nb |= (((reg >> 2) & (reg >> 5)) ^ (reg >> 0) & (reg >> 4)) & 1 ;
	for (uint8_t j = 0; j < fb_size; ++j) { nb ^= reg >> fb[j]; }
	return (reg >> 1) | ((nb & 1) << 7);
}

std::vector<size_t> cycletype(std::function<uint8_t(uint8_t)> fb_func) {
	std::vector<size_t> res;

	bool vis[256] = {false};
	for (uint8_t state = 0x1; state != 0; ++state) {
		if (vis[state]) continue;

		std::unordered_map<uint8_t, size_t> st_map;
		uint8_t reg = state;
		while(true) {
			if (vis[reg]) { res.push_back(st_map.size()); break; }
			if (st_map.find(reg) != st_map.end()) { res.push_back(st_map.size() - st_map[reg]); break; }

			st_map[reg] = st_map.size();
			vis[reg] = true;
			reg = fb_func(reg);
		}
	}

	return res;
}


int main() {
	std::vector<size_t> sizes;
	for (uint8_t fb_bits = 1; fb_bits != 0; ++fb_bits) {
		uint8_t fb_arr[8] = {0}, fb_size = 0; 
		for (int i = 0; i < 8; ++i) if ((fb_bits >> i) & 1) fb_arr[fb_size++] = i;

		auto v = cycletype([&](uint8_t reg){ return nfsr_shift(reg, fb_arr, fb_size); });
		sizes.push_back(v.size());
	}

	std::sort(sizes.begin(), sizes.end(), [](size_t a, size_t b) {return a < b;});
	for (auto i: sizes) std::cout << i << ' ';

	return 0;
}
