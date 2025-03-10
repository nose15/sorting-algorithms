//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_HEAPSORT_HPP
#define AIZO_1_HEAPSORT_HPP

#include "../sorting_algorithm/SortingAlgorithm.hpp"

namespace Sorting {

    class HeapSort : public SortingAlgorithm {
    public:
        HeapSort(int32_t* arr, size_t size);
        int32_t* sort() override;
        ~HeapSort() = default;
    };

} // Sorting

#endif //AIZO_1_HEAPSORT_HPP
