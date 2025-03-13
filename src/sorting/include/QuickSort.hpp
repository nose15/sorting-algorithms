//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_QUICKSORT_HPP
#define AIZO_1_QUICKSORT_HPP

#include <SortingAlgorithm.hpp>

namespace Sorting {

    class QuickSort : public SortingAlgorithm {
    public:
        using SortingAlgorithm::SortingAlgorithm;
        int32_t* sort() override;
        ~QuickSort() override = default;
    };

} // Sorting

#endif //AIZO_1_QUICKSORT_HPP
