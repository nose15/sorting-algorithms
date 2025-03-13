//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_HEAPSORT_HPP
#define AIZO_1_HEAPSORT_HPP

#include <cstring>
#include <vector>
#include <SortingAlgorithm.hpp>

namespace Sorting {

    class HeapSort : public SortingAlgorithm {
    public:
        HeapSort() = default;
        HeapSort(int32_t* arr, size_t size);
        int32_t* sort() override;
        ~HeapSort() override = default;
    };

} // Sorting

#endif //AIZO_1_HEAPSORT_HPP
