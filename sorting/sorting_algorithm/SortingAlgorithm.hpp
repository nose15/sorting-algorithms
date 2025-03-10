//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_SORTINGALGORITHM_HPP
#define AIZO_1_SORTINGALGORITHM_HPP

#include <cstddef>
#include <cstdint>

namespace Sorting {
    class SortingAlgorithm {
    protected:
        int32_t * arr;
        size_t size;
    public:
        SortingAlgorithm();
        void setArray(int32_t * arr, size_t size);
        virtual int32_t* sort() = 0;
        ~SortingAlgorithm();
    };
} // Sorting

#endif //AIZO_1_SORTINGALGORITHM_HPP
