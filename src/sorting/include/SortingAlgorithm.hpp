//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_SORTINGALGORITHM_HPP
#define AIZO_1_SORTINGALGORITHM_HPP

#include <cstddef>
#include <cstdint>
#include <algorithm>

namespace Sorting {

    template <typename T>
    class SortingAlgorithm {
    protected:
        T * arr;
        size_t size;
    public:
        SortingAlgorithm() {
            arr = nullptr;
            size = 0;
        }

        SortingAlgorithm(T * arr, size_t size) {
            this->arr = new T[size];
            std::copy(arr, arr + size, this->arr);
            this->size = size;
        }
        void setArray(T * arr, size_t size) {
            this->arr = new T[size];
            std::copy(arr, arr + size, this->arr);
            this->size = size;
        }
        virtual T* sort() = 0;
        virtual ~SortingAlgorithm() {
            delete this->arr;
        }
    };
} // Sorting

#endif //AIZO_1_SORTINGALGORITHM_HPP
