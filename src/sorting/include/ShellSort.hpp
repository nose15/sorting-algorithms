//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_SHELLSORT_HPP
#define AIZO_1_SHELLSORT_HPP

#include <cstring>
#include <SortingAlgorithm.hpp>

namespace Sorting {
    enum GapFormula {
      GF_SHELL = 1,
      GF_HIBBARD = 2,
    };

    template <typename T>
    class ShellSort : public SortingAlgorithm<T> {
     private:
        GapFormula gap_formula;
     public:
        using SortingAlgorithm<T>::SortingAlgorithm;

        ShellSort<T>(T * arr, size_t size, GapFormula gapFormula, std::string config_info) : SortingAlgorithm<T>(arr, size, config_info) {
          this->gap_formula = GapFormula(gapFormula);
        }

        ShellSort<T>(T * arr, size_t size, GapFormula gapFormula) : SortingAlgorithm<T>(arr, size) {
          this->gap_formula = GapFormula(gapFormula);
        }

        T* sort() override {
          int * gaps = new int[this->size];
          int gap_size = 0;

          if (this->gap_formula == GF_SHELL) {
            int s = 0;

            for (int n = 1; n < this->size; n *= 2) {
              gaps[s] = n;
              s++;
            }

            gap_size = s;
          } else if (this->gap_formula == GF_HIBBARD) {
            int s = 0;

            for (int n = 1; n < this->size; n = (n << 1) + 1) {
              gaps[s] = n;
              s++;
            }

            gap_size = s;
          }

          for (int g = gap_size - 1; g >= 0; g--) {
            for (uint32_t i = gaps[g]; i < this->size; ++i) {
              T temp = this->arr[i];
              uint32_t j = i;

              while (j >= gaps[g] && this->arr[j - gaps[g]] > temp) {
                this->arr[j] = this->arr[j - gaps[g]];
                j -= gaps[g];
              }

              this->arr[j] = temp;
            }
          }

          return this->arr;
        }

        std::string getConfig() override {
          std::string config_str = "shell_sort;" + this->config_info + std::to_string(this->gap_formula) + ";";
          return config_str;
        }

        ~ShellSort() override = default;
    };

} // Sorting

#endif //AIZO_1_SHELLSORT_HPP
