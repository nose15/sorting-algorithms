//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_SHELLSORT_HPP
#define AIZO_1_SHELLSORT_HPP

#include "../sorting_algorithm/SortingAlgorithm.hpp"

namespace Sorting {

    class ShellSort : public SortingAlgorithm {
    public:
        ShellSort(int32_t* arr, size_t size);
        int32_t* sort() override;
        ~ShellSort() = default;
    };

} // Sorting

#endif //AIZO_1_SHELLSORT_HPP
