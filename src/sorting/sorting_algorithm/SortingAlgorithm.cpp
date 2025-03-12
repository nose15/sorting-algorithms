//
// Created by lukasz on 10.03.25.
//
#include "SortingAlgorithm.hpp"

namespace Sorting {
    void SortingAlgorithm::setArray(int32_t* arr, size_t size) {

    }

    SortingAlgorithm::SortingAlgorithm() {
        arr = nullptr;
        size = 0;
    }

    SortingAlgorithm::~SortingAlgorithm() {
        delete this->arr;
    }
}
