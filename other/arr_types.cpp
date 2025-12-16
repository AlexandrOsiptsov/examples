#include <iostream>

int main() {

    int arr[10];
    int* dyn_arr_ptr = new int[10];
    int (*stat_arr_ptr)[10];
    int* ptrs_arr[10];
    
    std::cout << "arr            " << typeid(arr).name() << '\n';
    std::cout << "dyn_arr_ptr    " << typeid(dyn_arr_ptr).name() << '\n';
    std::cout << "stat_arr_ptr   " << typeid(stat_arr_ptr).name() << '\n';
    std::cout << "ptrs_arr       " << typeid(ptrs_arr).name() << '\n';
    
    
    // базовые (примитивы) и производные типы
    
    // arr            A10_i
    // dyn_arr_ptr    Pi
    // stat_arr_ptr   PA10_i
    // ptrs_arr       A10_Pi

    return 0;
}
