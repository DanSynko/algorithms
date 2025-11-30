#include <iostream>
#include <vector>
#include "algorithms_timer.h"
#include <random>

void bubble_sort(std::vector<int>& vec) {
    int sort_count = 0;
    bool arr_is_not_sorted = true;
    while (arr_is_not_sorted) {
        for (int i = 0; i < vec.size() - 1; i++) {
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                sort_count++;
            }
        }
        if (sort_count == 0) arr_is_not_sorted = false;
        else {
            sort_count = 0;
            continue;
        }
    }
}

auto random_arr() {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> dist(0, 4999999);
    std::vector<int> vec = {};
    // test size
    const int elements = 999;
    vec.reserve(elements);
    for (int i = 0; i < elements; i++) {
        vec.push_back(dist(engine));
    }
    return vec;
}

int main() {
    std::vector<int> demo_vec = { 20, 10, 72, 39, 94, 96, 82, 823, 3, 345, 87 };
    // needed result: 3, 10, 20, 39, 72, 82, 87, 94, 96, 345, 823;

    std::cout << "Vector before bubble sort: ";
    for (const int& i : demo_vec) {
        std::cout << i << ". ";
    }
    std::cout << std::endl;
    bubble_sort(demo_vec);
    std::cout << "Vector after: ";
    for (const int& i : demo_vec) {
        std::cout << i << ". ";
    }
    std::cout << std::endl;


    demo_vec.clear();
    demo_vec = random_arr();
    auto sort_timer = alg_timer::Timer::code_timer([&]() {
        bubble_sort(demo_vec);
    });
    auto sort_time_info = sort_timer.count();
    std::cout << "Execution time of algorithm: " << sort_time_info << "ns." << std::endl;

    return 0;
}