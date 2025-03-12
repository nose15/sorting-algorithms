//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_QUICKSORT_HPP
#define AIZO_1_QUICKSORT_HPP

#include <SortingAlgorithm.hpp>

namespace Sorting {

    class QuickSort : public SortingAlgorithm {
    public:
        QuickSort(int32_t* arr, size_t size);
        int32_t* sort() override;
        ~QuickSort() = default;
    };

} // Sorting

#endif //AIZO_1_QUICKSORT_HPP
