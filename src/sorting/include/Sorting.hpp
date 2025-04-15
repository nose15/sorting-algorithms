#ifndef AIZO_1_SORTING_HPP
#define AIZO_1_SORTING_HPP

#include <filesystem>
#include <iostream>
#include "HeapSort.hpp"
#include "InsertionSort.hpp"
#include "QuickSort.hpp"
#include "ShellSort.hpp"
#include "Multithreading.hpp"
#include "FileUtils.hpp"
#include <MeasurementUtils.hpp>

namespace Sorting {
  enum Algorithm {
    INSERTION = 1,
    HEAP = 2,
    QUICK = 3,
    SHELL = 4,
  };

  void createAlgorithms(const std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>& algorithmQueue);
  std::unique_ptr<Sorting::AlgorithmBenchmark> createBenchmarkFromFile(const std::filesystem::path& file, std::unordered_map<std::string, std::string>& flags);

  template <typename T>
  std::unique_ptr<Sorting::AlgorithmBenchmark> createBenchmark(Algorithm algorithm, std::unique_ptr<T[]> arr, size_t len) {
    std::unique_ptr<Sorting::AlgorithmBenchmark> algoBenchmark;

    switch (algorithm) {
      case INSERTION:
        algoBenchmark = std::make_unique<Sorting::InsertionSort<T>>(arr.get(), len);
        break;

      case HEAP:
        algoBenchmark = std::make_unique<Sorting::HeapSort<T>>(arr.get(), len);
        break;

      case QUICK:
        algoBenchmark = std::make_unique<Sorting::QuickSort<T>>(arr.get(), len);
        break;

      case SHELL:
        algoBenchmark = std::make_unique<Sorting::ShellSort<T>>(arr.get(), len);
        break;
    }

    return std::move(algoBenchmark);
  }


  template <typename T>
  void createBenchmarksFromFile(const std::filesystem::directory_entry & f, const std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>& algorithmQueue) {
    std::shared_ptr<T[]> arr;
    size_t len = FileUtils::readArr(f.path(), arr);

    algorithmQueue->push(std::make_unique<Sorting::HeapSort<T>>(arr.get(), len));
    algorithmQueue->push(std::make_unique<Sorting::InsertionSort<T>>(arr.get(), len));
    algorithmQueue->push(std::make_unique<Sorting::QuickSort<T>>(arr.get(), len, Sorting::Pivot::LEFT));
    algorithmQueue->push(std::make_unique<Sorting::QuickSort<T>>(arr.get(), len, Sorting::Pivot::RIGHT));
    algorithmQueue->push(std::make_unique<Sorting::QuickSort<T>>(arr.get(), len, Sorting::Pivot::MIDDLE));
    algorithmQueue->push(std::make_unique<Sorting::ShellSort<T>>(arr.get(), len));
  }
}

#endif
