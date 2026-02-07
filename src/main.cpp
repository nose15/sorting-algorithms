#include <iostream>
#include <filesystem>
#include <set>
#include <Sorting.hpp>
#include <Multithreading.hpp>
#include <MeasurementUtils.hpp>

void concurrentRun();
void singleRun(const std::string& fileName, const std::filesystem::path& resultPath, std::unordered_map<std::string, std::string>& flags);
void readCLIArgs(int argc, char** argv, std::unordered_map<std::string, std::string>& flags);
void runDialog();
void * algorithmBenchmark(void * benchmarkArgs);

struct BenchmarkArgs {
  uint32_t core_number = -1;
  std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue;
};

int main(int argc, char** argv) {
    std::unordered_map<std::string, std::string> flags;
    readCLIArgs(argc, argv, flags);
    std::filesystem::path resultPath;

    try {
        if (flags.find("result") != flags.end()) {
            std::string fileName = flags["result"];
            if (fileName.empty()) throw std::invalid_argument("No file name specified");

            bool exists = std::filesystem::exists(fileName.c_str());
            if (!exists) throw std::invalid_argument("Wrong file name specified");

            resultPath = fileName;
        }

        if (flags.find("auto") != flags.end()) {
            std::cout << "Running automatic benchmark..." << std::endl;
            concurrentRun();
            return 0;
        } else if (flags.find("file") != flags.end()) {
            std::string fileName = flags["file"];
            if (fileName.empty()) throw std::invalid_argument("No file name specified");
            singleRun(fileName, resultPath, flags);
            return 0;
        }
    } catch (std::logic_error& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }

    runDialog();
}

// measuring
void singleRun(const std::string& fileName, const std::filesystem::path& resultPath, std::unordered_map<std::string, std::string>& flags) {
    std::filesystem::path file(fileName.c_str());
    if (!std::filesystem::exists(file)) throw std::invalid_argument("Wrong file name specified");

    if (!resultPath.empty() && !std::filesystem::is_regular_file(resultPath)) throw std::invalid_argument("Specified path to result is not a file");

    auto algoBenchmark = Sorting::createBenchmarkFromFile(file, flags);
    std::cout << "Running algorithm " << std::endl;
    algoBenchmark->run(false);
    std::cout << "Finished running " << std::endl;
}

template <typename T>
std::unique_ptr<T[]> sortUI(std::shared_ptr<T[]>& arr, int arr_size) {
  int alg = 0;
  while (alg < 1 || alg > 4) {
    std::cout << "Pick a sorting algorithm:\n"
                 "1. Insertion Sort\n"
                 "2. Heap Sort\n"
                 "3. Shell Sort\n"
                 "4. QuickSort\n"
                 "> ";
    std::cin >> alg;

    if (alg < 1 || alg > 4) {
      std::cout << "WRONG INPUT" << std::endl;
    }
  }

  std::unique_ptr<Sorting::SortingAlgorithm<T>> algorithm;

  switch (alg) {
    case 1:
      algorithm = std::make_unique<Sorting::InsertionSort<T>>(arr.get(), arr_size);
      break;
    case 2:
      algorithm = std::make_unique<Sorting::HeapSort<T>>(arr.get(), arr_size);
      break;
    case 3: {
      int gapForm = 0;
      while (gapForm != 1 && gapForm != 2) {
        std::cout << "Pick gap formula\n"
                     "1. Shell (N/(2^k))\n"
                     "2. Hibbard (2^k - 1)\n"
                     "> ";
        std::cin >> gapForm;

        if (gapForm != 1 && gapForm != 2) {
          std::cout << "WRONG INPUT" << std::endl;
        }
      }

      algorithm = std::make_unique<Sorting::ShellSort<T>>(arr.get(), arr_size, Sorting::GapFormula(gapForm));
      break;
    }
    case 4: {
      int pivot = 0;
      while (pivot < 1 || pivot > 4) {
        std::cout << "Pick the pivot\n"
                     "1. right\n"
                     "2. left\n"
                     "3. middle\n"
                     "4. random\n"
                     "> ";
        std::cin >> pivot;

        if (pivot < 1 || pivot > 4) {
          std::cout << "WRONG INPUT" << std::endl;
        }
      }

      algorithm = std::make_unique<Sorting::QuickSort<T>>(arr.get(), arr_size, Sorting::Pivot(pivot - 1));
      break;
    }
    default:
      exit(alg);
  }

  T* sorted = algorithm->sort();
  T* sortedArr = new T[arr_size];
  std::copy(sorted, sorted + arr_size, sortedArr);
  std::cout << "Sorted array: " << std::endl;
  for (int i = 0; i < arr_size; i++) {
    std::cout << sortedArr[i] << " ";
  }
  std::cout << std::endl;

  return std::unique_ptr<T[]>(sortedArr);
}

template <typename T>
int generateArrayUI(std::shared_ptr<T[]>& arr) {
  int arrSize = 0;
  while (arrSize < 1) {
    std::cout << "Array size: ";
    std::cin >> arrSize;

    if (arrSize < 1) {
      std::cout << "WRONG INPUT";
    }
  }

  int conf = 0;
  while (conf < 1 || conf > 5) {
    std::cout << "Array initial state:\n"
                 "1. Random\n"
                 "2. 33% sorted\n"
                 "3. 66% sorted\n"
                 "4. Fully sorted\n"
                 "5. Sorted in reverse\n"
                 "> ";
    std::cin >> conf;

    if (conf < 1 || conf > 5) {
      std::cout << "WRONG INPUT" << std::endl;
    }
  }

  arr = generateArr<T>(arrSize, conf);
  std::cout << "Array generated successfully" << std::endl;
  return arrSize;
}


template <typename T>
int loadArray(std::shared_ptr<T[]>& arr) {
  std::string fileName;

  while (true) {
    std::cout << "File name: ";
    std::cin >> fileName;

    try {
      auto path = std::filesystem::path(std::filesystem::current_path().string() + "/" + fileName);
      std::cout << "Trying to read: " << path << std::endl;
      int len = FileUtils::readArr<T>(path, arr);
      std::cout << "Array loaded successfully" << std::endl;
      return len;
    } catch (std::length_error &e) {
      std::cout << "WRONG INPUT" << std::endl;
      continue;
    }
  }
}

template <typename T>
void executeDialog() {
  std::shared_ptr<T[]> arr;
  std::unique_ptr<T[]> sorted;

  int arr_size = 0;

  while (true) {
    int operation = -1;
    while (operation < 0 || operation > 5) {
      std::cout << "What would you like to do?\n"
                   "1. Load an array from file\n"
                   "2. Generate an array\n"
                   "3. Display the loaded array\n"
                   "4. Sort the loaded array\n"
                   "5. Display the sorted array\n"
                   "0. Exit\n"
                   "> ";

      std::cin >> operation;

      if (operation < 0 || operation > 5) {
        std::cout << "WRONG INPUT" << std::endl;
      }
    }

    switch (operation) {
      case 1:
        arr_size = loadArray<T>(arr);
        break;
      case 2:
        arr_size = generateArrayUI<T>(arr);
        break;
      case 3:
        for (int i = 0; i < arr_size; i++) {
          std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        break;
      case 4:
        sorted = std::move(sortUI<T>(arr, arr_size));
        break;
      case 5:
        for (int i = 0; i < arr_size; i++) {
          std::cout << sorted[i] << " ";
        }
        std::cout << std::endl;
        break;
      default:
        std::cout << "Closing" << std::endl;
        exit(operation);
    }
    std::cout << std::endl;
  }
}

// CLI method
void runDialog() {
  int dataType = 0;
  while (dataType != 1 && dataType != 2) {
    std::cout << "Pick a datatype (1. int, 2. float): ";
    std::cin >> dataType;

    if (dataType != 1 && dataType != 2) {
      std::cout << "WRONG INPUT " << (dataType == 1) << std::endl;
    }
  }

  switch (dataType) {
    case 1:
      executeDialog<int32_t>();
      break;
    case 2:
      executeDialog<double>();
      break;
    default:
      exit(dataType);
  }
}

// CLI method
void readCLIArgs(int argc, char** argv, std::unordered_map<std::string, std::string>& flags) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (i + 1 < argc && arg.size() > 2 && arg.substr(0, 2) == "--") {
            std::string param(argv[i + 1]);

            if (param.size() > 2 && param.substr(0, 2) != "--") {
                flags.emplace(arg.substr(2), param);
                i++;
            }
        }

        flags.emplace(arg.substr(2), "");
    }
}

// measuring
void concurrentRun() {
    auto isolatedCpus = Multithreading::getIsolatedCpus();
    const uint32_t threadCount = isolatedCpus.size();

    auto threads = new pthread_t[threadCount];
    auto algorithms = std::make_shared<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>();

    Sorting::createAlgorithms(algorithms);
    BenchmarkArgs * benchmarkArgArr[threadCount];

    for (uint32_t i = 0; i < threadCount; i++) {
      // This gets deleted in the thread - can actually delete it in join
      benchmarkArgArr[i] = new BenchmarkArgs;
      benchmarkArgArr[i]->algorithmQueue = algorithms;

      std::cout << "Core " << isolatedCpus[i] << std::endl;

      benchmarkArgArr[i]->core_number = isolatedCpus[i];

      pthread_create(&threads[i], nullptr, algorithmBenchmark, benchmarkArgArr[i]);
    }

    for (uint32_t i = 0; i < threadCount; i++) {
      pthread_join(threads[i], nullptr);
      delete benchmarkArgArr[i];
    }

    delete[] threads;
}

// measuring
void * algorithmBenchmark(void * benchmarkArgs) {
    auto * args = (BenchmarkArgs *) benchmarkArgs;

    if (args->core_number == -1) return nullptr;

    // Bind the thread to the isolated core
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(args->core_number, &cpu_set);
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu_set);

    while (args->algorithmQueue->size() != 0) {
        auto algoBenchmark = args->algorithmQueue->pop();

        // timeout happened - queue likely empty
        if (algoBenchmark == nullptr) {
            return nullptr;
        }

        double time = algoBenchmark->run(false);
        std::string conf = algoBenchmark->getConfig() + std::to_string(time) + ";";
        printf("%s\n", conf.c_str());
    }


    pthread_exit(nullptr);
}
