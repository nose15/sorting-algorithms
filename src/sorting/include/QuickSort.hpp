//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_QUICKSORT_HPP
#define AIZO_1_QUICKSORT_HPP

#include <SortingAlgorithm.hpp>

namespace Sorting {
    template <typename T>
    class QuickSort : public SortingAlgorithm<T> {
    private:
        void quicksort(int32_t l, int32_t r) {
            if (l >= r) return;
            int32_t pivot = partition(l, r);
            quicksort(l, pivot - 1);
            quicksort(pivot + 1, r);
        }

        int32_t partition(int32_t l, int32_t r) {
            T pivot = this->arr[r];
            int32_t i = l - 1;

            for (int32_t j = l; j < r; j++) {
                if (this->arr[j] < pivot) {
                    i++;
                    std::swap(this->arr[i], this->arr[j]);
                }
            }

            std::swap(this->arr[i + 1], this->arr[r]);

            return i + 1;
        }
    public:
        using SortingAlgorithm<T>::SortingAlgorithm;
        T* sort() override {
            quicksort(0, this->size - 1);
            return this->arr;
        }
        ~QuickSort() override = default;
    };

} // Sorting

#endif //AIZO_1_QUICKSORT_HPP
