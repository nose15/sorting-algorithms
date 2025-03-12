//
// Created by lukasz on 10.03.25.
//

#include <HeapSort.hpp>

namespace Sorting {
    HeapSort::HeapSort(int32_t *arr, size_t size) {
        this->arr = new int32_t[size];
        std::copy(arr, arr + size - 1, this->arr);
        this->size = size;
    }

    int32_t* HeapSort::sort() {
        // TODO: Implement heap sort

        return arr;
    }
} // Sorting