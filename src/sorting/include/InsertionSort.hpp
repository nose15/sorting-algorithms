//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_INSERTIONSORT_HPP
#define AIZO_1_INSERTIONSORT_HPP

#include <cstring>
#include <SortingAlgorithm.hpp>

namespace Sorting {
    template <typename T>
    class InsertionSort : public SortingAlgorithm<T> {
    private:
        void shiftRight(uint16_t start, uint16_t end) {
            if (end < start) {
                return;
            }

            for (int i = end; i > start; i--) {
                this->arr[i] = this->arr[i - 1];
            }
        }

    public:
        using SortingAlgorithm<T>::SortingAlgorithm;

        T* sort() override {
            for (int i = 1; i < this->size; i++) {
                int j = i - 1;
                while (j > 0 && this->arr[j - 1] > this->arr[i]) j--;

                if (this->arr[j] > this->arr[i]) {
                    T val = this->arr[i];
                    shiftRight(j, i);
                    this->arr[j] = val;
                }
            }

            return this->arr;
        }

        ~InsertionSort() override = default;
    };

} // Sorting

#endif //AIZO_1_INSERTIONSORT_HPP
