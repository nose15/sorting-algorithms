//
// Created by lukasz on 10.03.25.
//

#include <InsertionSort.hpp>
#include <algorithm>

namespace Sorting {
    InsertionSort::InsertionSort(int32_t *arr, size_t size) {
        this->arr = new int32_t[size];
        std::copy(arr, arr + size, this->arr);
        this->size = size;
    }

    int32_t* InsertionSort::sort() {
        // TODO: Implement insertion sort

        return arr;
    }
} // Sorting