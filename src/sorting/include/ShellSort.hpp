//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_SHELLSORT_HPP
#define AIZO_1_SHELLSORT_HPP

#include <cstring>
#include <SortingAlgorithm.hpp>

namespace Sorting {
    template <typename T>
    class ShellSort : public SortingAlgorithm<T> {
    public:
        using SortingAlgorithm<T>::SortingAlgorithm;
        T* sort() override {

        }
        ~ShellSort() override = default;
    };

} // Sorting

#endif //AIZO_1_SHELLSORT_HPP
