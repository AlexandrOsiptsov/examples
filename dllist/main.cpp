#include <iostream>
#include <stdexcept>
#include <vector>
#include "dllist.hpp"

int main() {
    try {
        std::vector<int> v {1, 2, 3, 4, 5, 6};
        DLList<int> l;

        for (const auto& e : v) {
            l.push_back(e);
        }

        while(l.size()) {
            std::cout << l.front() << ' ';
            l.pop_front();
        }
        std::cout << '\n';
        std::cout << l.size() << '\n';
    }
    catch (std::exception e) {
        std::cerr << "Exception caught: " << e.what() << '\n';
    }

    return 0;
}