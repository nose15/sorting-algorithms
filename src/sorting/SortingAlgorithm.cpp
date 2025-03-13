//
// Created by lukasz on 10.03.25.
//
#include <SortingAlgorithm.hpp>
#include <algorithm>

namespace Sorting {
    SortingAlgorithm::SortingAlgorithm() {
        arr = nullptr;
        size = 0;
    }

    SortingAlgorithm::SortingAlgorithm(int32_t *arr, size_t size) {
        this->arr = new int32_t[size];
        std::copy(arr, arr + size, this->arr);
        this->size = size;
    }

    void SortingAlgorithm::setArray(int32_t* arr, size_t size) {
        this->arr = new int32_t[size];
        std::copy(arr, arr + size, this->arr);
        this->size = size;
    }

    SortingAlgorithm::~SortingAlgorithm() {
        delete this->arr;
    }
}
