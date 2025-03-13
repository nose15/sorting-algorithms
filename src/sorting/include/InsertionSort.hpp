//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_INSERTIONSORT_HPP
#define AIZO_1_INSERTIONSORT_HPP

#include <cstring>
#include <SortingAlgorithm.hpp>

namespace Sorting {

    class InsertionSort : public SortingAlgorithm {
    public:
        using SortingAlgorithm::SortingAlgorithm;
        int32_t* sort() override;
        ~InsertionSort() override = default;
    };

} // Sorting

#endif //AIZO_1_INSERTIONSORT_HPP
