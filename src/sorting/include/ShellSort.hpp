//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_SHELLSORT_HPP
#define AIZO_1_SHELLSORT_HPP

#include <cstring>
#include <SortingAlgorithm.hpp>

namespace Sorting {
    template <typename T>
    class ShellSort : public SortingAlgorithm<T> {
     private:
        uint32_t jump;
     public:
        using SortingAlgorithm<T>::SortingAlgorithm;
        ShellSort<T>(T * arr, size_t size, uint32_t jump) : SortingAlgorithm<T>(arr, size) {
          if (jump > size) {
            throw std::runtime_error("Jump cannot be bigger than size");
          }
          this->jump = jump;
        }

        T* sort() override {
          uint32_t gap = jump;

          while (gap > 0) {
            for (uint32_t i = gap; i < this->size; ++i) {
              T temp = this->arr[i];
              uint32_t j = i;

              while (j >= gap && this->arr[j - gap] > temp) {
                this->arr[j] = this->arr[j - gap];
                j -= gap;
              }

              this->arr[j] = temp;
            }

            gap /= 2;
          }

          return this->arr;
        }
        ~ShellSort() override = default;
    };

} // Sorting

#endif //AIZO_1_SHELLSORT_HPP
