//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_QUICKSORT_HPP
#define AIZO_1_QUICKSORT_HPP

#include <SortingAlgorithm.hpp>

namespace Sorting {
    enum Pivot {
      RIGHT = 0,
      LEFT = 1,
      MIDDLE = 2,
    };

    template <typename T>
    class QuickSort : public SortingAlgorithm<T> {
    private:
        Pivot pivotMode = Pivot::LEFT;

        void quicksort(int32_t l, int32_t r)
        {
          if(r <= l) return;

          int32_t i = l - 1;
          int32_t j = r + 1;
          T pivot;

          switch (pivotMode) {
            case LEFT:   pivot = this->arr[l]; break;
            case RIGHT:  pivot = this->arr[r]; break;
            case MIDDLE: pivot = this->arr[(l + r) / 2]; break;
          }

          while(1)
          {
            while(pivot > this->arr[++i]);

            while(pivot < this->arr[--j]);

            if( i <= j)
              std::swap(this->arr[i],this->arr[j]);
            else
              break;
          }

          if(j > l)
            quicksort(l, j);
          if(i < r)
            quicksort(i, r);
        }
    public:
        using SortingAlgorithm<T>::SortingAlgorithm;
        QuickSort<T>(T * arr, size_t size, Pivot pivot, std::string config_info) : SortingAlgorithm<T>(arr, size, config_info) {
          pivotMode = pivot;
        }
        QuickSort<T>(T * arr, size_t size, Pivot pivot) : SortingAlgorithm<T>(arr, size) {
          pivotMode = pivot;
        }
        T* sort() override {
            quicksort(0, this->size - 1);
            return this->arr;
        }

        std::string getConfig() override {
          std::string config_str = "quick_sort;" + this->config_info + std::to_string(this->pivotMode) + ";";
          return config_str;
        }

      ~QuickSort() override = default;
    };

} // Sorting

#endif //AIZO_1_QUICKSORT_HPP
