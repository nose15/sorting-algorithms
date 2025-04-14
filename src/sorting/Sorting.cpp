//
// Created by lukasz on 14.04.25.
//

#include "Sorting.hpp"

namespace Sorting {
  void createAlgorithms(const std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>& algorithmQueue) {
    auto it = std::filesystem::directory_iterator("data");
    for (const auto & f : it) {
      if (!f.is_regular_file()) break;
      std::string path = f.path().string();
      uint16_t first_ = path.find('_');
      std::string datatype = path.substr(first_ + 1, 3);

      if (datatype == "int") {
        createBenchmarksFromFile<int32_t>(f, algorithmQueue);
      }
      else if (datatype == "flo") {
        createBenchmarksFromFile<double>(f, algorithmQueue);
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