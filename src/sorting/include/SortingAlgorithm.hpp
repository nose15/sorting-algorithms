//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_SORTINGALGORITHM_HPP
#define AIZO_1_SORTINGALGORITHM_HPP

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <AlgorithmBenchmark.hpp>

namespace Sorting {

    template <typename T>
    class SortingAlgorithm : public AlgorithmBenchmark {
    protected:
        T * arr;
        size_t size;
    public:
        SortingAlgorithm() {
            arr = nullptr;
            size = 0;
        }

        SortingAlgorithm(T * arr, size_t size) {
            this->arr = new T[size];
            std::copy(arr, arr + size, this->arr);
            this->size = size;
        }

        ~SortingAlgorithm() override {
            delete this->arr;
        }

        virtual T* sort() = 0;

        void run() override {
            // get time before

            T* sorted = sort();

            std::cout << "After: " << sorted[0] << std::endl;
//            for (size_t i = 0; i < size; i++) {
//                std::cout << sorted[i] << " ";
//            }
//            std::cout << std::endl;

            // get time after, get total time

            // if properly sorted - save to file
        }
    };
} // Sorting

#endif //AIZO_1_SORTINGALGORITHM_HPP
