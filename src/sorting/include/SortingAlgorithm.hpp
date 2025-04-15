//
// Created by lukasz on 10.03.25.
//

#ifndef AIZO_1_SORTINGALGORITHM_HPP
#define AIZO_1_SORTINGALGORITHM_HPP

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <AlgorithmBenchmark.hpp>
#include <chrono>
#include <utility>

namespace Sorting {

    template <typename T>
    class SortingAlgorithm : public AlgorithmBenchmark {
    protected:
        T * arr;
        size_t size;
        std::string config_info;
    public:
        SortingAlgorithm() {
            arr = nullptr;
            size = 0;
        }

        SortingAlgorithm(T * arr, size_t size, const std::string& config_info) {
          this->config_info = std::to_string(size) + ";" + config_info + ";";
          this->arr = new T[size];
          std::copy(arr, arr + size, this->arr);
          this->size = size;
        }

        SortingAlgorithm(T * arr, size_t size) {
            this->config_info = std::to_string(size) + ";;";
            this->arr = new T[size];
            std::copy(arr, arr + size, this->arr);
            this->size = size;
        }

        ~SortingAlgorithm() override {
            delete this->arr;
        }

        virtual T* sort() = 0;

        double run() override {
            auto start = std::chrono::high_resolution_clock::now();
            T* sorted = sort();
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;
            return duration.count();
        }
    };
} // Sorting

#endif //AIZO_1_SORTINGALGORITHM_HPP
