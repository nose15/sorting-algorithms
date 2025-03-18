//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_QUICKSORT_HPP
#define AIZO_1_QUICKSORT_HPP

#include <SortingAlgorithm.hpp>

namespace Sorting {
    template <typename T>
    class QuickSort : public SortingAlgorithm<T> {
    public:
        using SortingAlgorithm<T>::SortingAlgorithm;
        T* sort() override {

        }
        ~QuickSort() override = default;
    };

} // Sorting

#endif //AIZO_1_QUICKSORT_HPP
