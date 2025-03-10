//
// Created by lukasz on 10.03.25.
//
#include "SortingAlgorithm.hpp"

void Sorting::SortingAlgorithm::setArray(int32_t* arr, size_t size) {

}

Sorting::SortingAlgorithm::SortingAlgorithm() {
    arr = nullptr;
    size = 0;
}

Sorting::SortingAlgorithm::~SortingAlgorithm() {
    delete this->arr;
}
