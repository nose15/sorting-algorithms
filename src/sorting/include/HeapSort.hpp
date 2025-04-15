//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_HEAPSORT_HPP
#define AIZO_1_HEAPSORT_HPP

#include <cstring>
#include <vector>
#include <SortingAlgorithm.hpp>

namespace Sorting {
    template <typename T>
    class HeapSort : public SortingAlgorithm<T> {
     private:
      void heapify(int32_t index, int32_t last) {
        T value = this->arr[index];
        int32_t child = 2 * index + 1;

        while (child <= last) {
          if (child + 1 <= last && this->arr[child + 1] > this->arr[child]) {
            child++;
          }

          if (this->arr[child] > value) {
            this->arr[index] = this->arr[child];
            index = child;
            child = 2 * index + 1;
          } else {
            break;
          }
        }

        this->arr[index] = value;
      }

     public:
        using SortingAlgorithm<T>::SortingAlgorithm;

        T* sort() override {
          for (int32_t i = (this->size / 2) - 1; i >= 0; --i) {
            heapify(i, this->size - 1);
          }

          for (int32_t sortedBound = this->size - 1; sortedBound > 0; --sortedBound) {
            std::swap(this->arr[0], this->arr[sortedBound]);
            heapify(0, sortedBound - 1);
          }

          return this->arr;
        }

        ~HeapSort() override = default;
    };
} // Sorting

#endif //AIZO_1_HEAPSORT_HPP
