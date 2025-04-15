//
// Created by lukasz on 14.04.25.
//

#include "Sorting.hpp"

namespace Sorting {
  void createAlgorithms(const std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>& algorithmQueue) {
    int size[20]{1000, 2500, 5000, 7500, 10000, 25000, 30000, 35000, 40000, 45000, 50000, 60000, 70000, 80000, 90000, 100000, 150000, 200000, 400000, 600000};

    for (int i = 1; i <= 5; i++) {
      for (int & s : size) {
        // generate arr
        auto intArr = generateArr<int32_t>(s,i);
        auto floatArr = generateArr<double>(s,i);

        algorithmQueue->push(std::make_unique<QuickSort<int32_t>>(intArr.get(), s, Pivot::LEFT, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<QuickSort<int32_t>>(intArr.get(), s, Pivot::RIGHT, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<QuickSort<int32_t>>(intArr.get(), s, Pivot::MIDDLE, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<QuickSort<double>>(floatArr.get(), s, Pivot::LEFT, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<QuickSort<double>>(floatArr.get(), s, Pivot::RIGHT, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<QuickSort<double>>(floatArr.get(), s, Pivot::MIDDLE, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<QuickSort<double>>(floatArr.get(), s, Pivot::MIDDLE, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<QuickSort<double>>(floatArr.get(), s, Pivot::MIDDLE, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<ShellSort<int32_t>>(intArr.get(), s, s / 2, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<ShellSort<int32_t>>(intArr.get(), s, s / 4, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<ShellSort<int32_t>>(intArr.get(), s, s / 8, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<ShellSort<int32_t>>(intArr.get(), s, s / 20, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<ShellSort<int32_t>>(intArr.get(), s, s / 40, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<ShellSort<double>>(floatArr.get(), s, s / 2, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<ShellSort<double>>(floatArr.get(), s, s / 4, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<ShellSort<double>>(floatArr.get(), s, s / 8, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<ShellSort<double>>(floatArr.get(), s, s / 20, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<ShellSort<double>>(floatArr.get(), s, s / 40, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<InsertionSort<int32_t>>(intArr.get(), s, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<InsertionSort<int32_t>>(intArr.get(), s, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<InsertionSort<int32_t>>(intArr.get(), s, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<InsertionSort<double>>(floatArr.get(), s, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<InsertionSort<double>>(floatArr.get(), s, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<InsertionSort<double>>(floatArr.get(), s, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<HeapSort<int32_t>>(intArr.get(), s, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<HeapSort<int32_t>>(intArr.get(), s, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<HeapSort<int32_t>>(intArr.get(), s, std::to_string(i) + ";int"));
        algorithmQueue->push(std::make_unique<HeapSort<double>>(floatArr.get(), s, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<HeapSort<double>>(floatArr.get(), s, std::to_string(i) + ";double"));
        algorithmQueue->push(std::make_unique<HeapSort<double>>(floatArr.get(), s, std::to_string(i) + ";double"));
      }
    }
  }

  std::unique_ptr<Sorting::AlgorithmBenchmark> createBenchmarkFromFile(const std::filesystem::path& file, std::unordered_map<std::string, std::string>& flags) {
    std::unique_ptr<Sorting::AlgorithmBenchmark> algoBenchmark;

    Algorithm algorithm = INSERTION;
    if (flags.find("algo") != flags.end()) {
      if (flags["algo"] == "heap") algorithm = HEAP;
      else if (flags["algo"] == "quick") algorithm = QUICK;
      else if (flags["algo"] == "shell") algorithm = SHELL;
      else std::cout << "No such algorithm - defaulting to Insertion...";
    }

    if (flags.find("type") != flags.end()) {
      std::string type = flags["type"];

      if (type == "int") {
        std::shared_ptr<int32_t[]> arr;
        size_t len = FileUtils::readArr<int32_t>(file, arr);

        switch (algorithm) {
          case HEAP:
            algoBenchmark = std::make_unique<Sorting::HeapSort<int32_t>>(arr.get(), len);
            break;
          case INSERTION:
            algoBenchmark = std::make_unique<Sorting::InsertionSort<int32_t>>(arr.get(), len);
            break;
          case QUICK:
            algoBenchmark = std::make_unique<Sorting::QuickSort<int32_t>>(arr.get(), len);
            break;
          case SHELL:
            algoBenchmark = std::make_unique<Sorting::ShellSort<int32_t>>(arr.get(), len);
            break;
        }
      } else if (type == "double") {
        std::shared_ptr<double[]> arr;
        size_t len = FileUtils::readArr<double>(file, arr);

        switch (algorithm) {
          case HEAP:
            algoBenchmark = std::make_unique<Sorting::HeapSort<double>>(arr.get(), len);
            break;
          case INSERTION:
            algoBenchmark = std::make_unique<Sorting::InsertionSort<double>>(arr.get(), len);
            break;
          case QUICK:
            algoBenchmark = std::make_unique<Sorting::QuickSort<double>>(arr.get(), len);
            break;
          case SHELL:
            algoBenchmark = std::make_unique<Sorting::ShellSort<double>>(arr.get(), len);
            break;
        }
      }
    } else {
      std::shared_ptr<int32_t[]> arr;
      size_t len = FileUtils::readArr<int32_t>(file, arr);

      switch (algorithm) {
        case HEAP:
          algoBenchmark = std::make_unique<Sorting::HeapSort<int32_t>>(arr.get(), len);
          break;
        case INSERTION:
          algoBenchmark = std::make_unique<Sorting::InsertionSort<int32_t>>(arr.get(), len);
          break;
        case QUICK:
          algoBenchmark = std::make_unique<Sorting::QuickSort<int32_t>>(arr.get(), len);
          break;
        case SHELL:
          algoBenchmark = std::make_unique<Sorting::ShellSort<int32_t>>(arr.get(), len);
          break;
      }
    }

    return std::move(algoBenchmark);
  }
}