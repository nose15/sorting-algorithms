//
// Created by lukasz on 12.03.25.
//
#include <random>
#include <gtest/gtest.h>
#include <HeapSort.hpp>

TEST(HeapSortTest, TestSortingRandomArray) {
    size_t size = 20000;
    int32_t arr[20000];

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int32_t> dist(1, 10);

    for (int i = 0; i < size - 1; i++) {
        arr[i] = dist(mt);
    }

    Sorting::HeapSort heapSort(arr, size);
    int32_t* res = heapSort.sort();

    bool sorted = true;
    for (int i = 0; i < size - 1; i++) {
        if (res[i+1] < res[i]) {
            sorted = false;
            break;
        }
    }

    ASSERT_EQ(sorted, true);
}