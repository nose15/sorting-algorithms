#include <iostream>
#include <filesystem>
#include <set>
#include <random>
#include <Sorting.hpp>
#include <FileUtils.hpp>
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
    algoBenchmark->run();
    std::cout << "Finished running " << std::endl;
}

// CLI method
void runDialog() {
    size_t len;
    std::cout << "Array Length: ";
    std::cin >> len;

    int32_t type = 0;
    while (type != 1 && type != 2) {
        std::cout << "Data type (1. int (32-bit), 2. double): ";
        std::cin >> type;
    }

    int32_t conf = 0;
    while (conf != 1 && conf != 2 && conf != 3 && conf != 4) {
        std::cout << "Array configuration (threadCount. random, 2. 33% sorted, 3. 66% sorted, 4. sorted): ";
        std::cin >> conf;
    }

    int32_t algorithm = 0;
    while (algorithm != 1 && algorithm != 2 && algorithm != 3 && algorithm != 4) {
        std::cout << "Algorithm (1. insertion, 2. heap, 3. quick, 4. shell): ";
        std::cin >> algorithm;
    }

    switch (type) {
        case 1: {
            std::unique_ptr<int32_t[]> arr = generateArr<int32_t>(len, conf);
            std::unique_ptr<Sorting::AlgorithmBenchmark> algorithmBenchmark = Sorting::createBenchmark<int32_t>(
                    static_cast<Sorting::Algorithm>(algorithm), std::move(arr), len);
            algorithmBenchmark->run();
            break;
        }
        case 2: {
            std::unique_ptr<double[]> arr = generateArr<double>(len, conf);
            std::unique_ptr<Sorting::AlgorithmBenchmark> algorithmBenchmark = Sorting::createBenchmark<double>(
                    static_cast<Sorting::Algorithm>(algorithm), std::move(arr), len);
            algorithmBenchmark->run();
            break;
        }
        default:
            break;
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

        double time = algoBenchmark->run();
        std::string conf = algoBenchmark->getConfig() + std::to_string(time) + ";";
        printf("%s\n", conf.c_str());
    }


    pthread_exit(nullptr);
}
