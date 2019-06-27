#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "sort.h"


std::chrono::milliseconds testArraySort(unsigned size) {
    std::vector<int> arr(size);
    for(auto i = 0; i < size; i++) {
        //arr[i] = std::rand() % 1000;
        arr[i] = std::rand();
    }

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    my::quick_sort(arr.begin(), arr.end());
    // my::merge_sort_recursive(arr.begin(), arr.end());
    // my::bottom_up_mergesort(arr.begin(), arr.end());
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
}

std::chrono::milliseconds testListSort(unsigned size) {
    std::list<int> lst;
    for(auto i = 0; i < size; i++) {
        lst.push_back(std::rand() % 1000);
    }

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    my::list_mergesort(lst.begin(), lst.end());
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
}


template <typename ForwardIterator>
void printRange(const char* prefix, ForwardIterator first, ForwardIterator last) {
    std::cout << prefix;
    while(first != last)
        std::cout << *(first++) << ", ";
    std::cout << std::endl;
}


int main() {
    std::srand(std::time(0));

    std::vector<unsigned> sizes = {100000, 200000, 400000, 800000};
        for(auto sizeIt = sizes.begin(); sizeIt != sizes.end(); sizeIt++) {
        auto durationMs = testArraySort(*sizeIt);
        std::cout << "size =     " << *sizeIt << std::endl;
        std::cout << "duration(ms) = " << durationMs.count() << std::endl;
        std::cout << "================================" << std::endl;
    }

    return 0;
}

