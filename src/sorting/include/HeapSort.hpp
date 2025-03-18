//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_HEAPSORT_HPP
#define AIZO_1_HEAPSORT_HPP

#include <cstring>
#include <vector>
#include <SortingAlgorithm.hpp>

namespace Sorting {
    template <typename T>
    class HeapSort : public SortingAlgorithm<T> {
    public:
        using SortingAlgorithm<T>::SortingAlgorithm;

        T* sort() override {
            
        }

        ~HeapSort() override = default;
    };
} // Sorting

#endif //AIZO_1_HEAPSORT_HPP
