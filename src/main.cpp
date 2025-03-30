#include <iostream>
#include <BlockingQueue.hpp>
#include <SortingAlgorithm.hpp>
#include <filesystem>
#include <fstream>
#include <InsertionSort.hpp>
#include <HeapSort.hpp>
#include <QuickSort.hpp>
#include <ShellSort.hpp>
#include <set>
#include <random>

enum Algorithm {
    INSERTION = 1,
    HEAP = 2,
    QUICK = 3,
    SHELL = 4,
};

void algorithmBenchmark(const std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>& algorithmQueue);
void createAlgorithms(const std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>& algorithmQueue);

template <typename T>
void createBenchmarksFromFile(const std::filesystem::directory_entry & f, const std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>& algorithmQueue);

template <typename T>
size_t readArr(const std::filesystem::path & f, std::shared_ptr<T[]>& ref);

std::unique_ptr<Sorting::AlgorithmBenchmark> createFloatAlgorithm(const std::filesystem::directory_entry & f);
void concurrentRun();
void singleRun(const std::string& fileName, const std::filesystem::path& resultPath, std::unordered_map<std::string, std::string>& flags);
void readCLIArgs(int argc, char** argv, std::unordered_map<std::string, std::string>& flags);
std::unique_ptr<Sorting::AlgorithmBenchmark> createBenchmarkFromFile(const std::filesystem::path& file, std::unordered_map<std::string, std::string>& flags);
void runDialog();

template <typename T>
std::unique_ptr<Sorting::AlgorithmBenchmark> createBenchmark(Algorithm algorithm, std::unique_ptr<T[]> arr, size_t len);

template <typename T>
std::unique_ptr<T[]> generateArr(size_t len, int32_t conf);

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
            std::cout << "Running automatic benchmark..." << std::endl;
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

void singleRun(const std::string& fileName, const std::filesystem::path& resultPath, std::unordered_map<std::string, std::string>& flags) {
    std::filesystem::path file(fileName.c_str());
    if (!std::filesystem::exists(file)) throw std::invalid_argument("Wrong file name specified");

    if (!resultPath.empty() && !std::filesystem::is_regular_file(resultPath)) throw std::invalid_argument("Specified path to result is not a file");

    auto algoBenchmark = createBenchmarkFromFile(file, flags);
    std::cout << "Running algorithm " << std::endl;
    algoBenchmark->run();
    std::cout << "Finished running " << std::endl;
}

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
        std::cout << "Array configuration (1. random, 2. 33% sorted, 3. 66% sorted, 4. sorted): ";
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
            std::unique_ptr<Sorting::AlgorithmBenchmark> algorithmBenchmark = createBenchmark<int32_t>(
                    static_cast<Algorithm>(algorithm), std::move(arr), len);
            algorithmBenchmark->run();
            break;
        }
        case 2: {
            std::unique_ptr<double[]> arr = generateArr<double>(len, conf);
            std::unique_ptr<Sorting::AlgorithmBenchmark> algorithmBenchmark = createBenchmark<double>(
                    static_cast<Algorithm>(algorithm), std::move(arr), len);
            algorithmBenchmark->run();
            break;
        }
        default:
            break;
    }
}

template <typename T>
std::unique_ptr<T[]> generateArr(size_t len, int32_t conf) {
    std::unique_ptr<T[]> arr = std::make_unique<T[]>(len);

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> dist(0, 10000); // define the range

    for (int i = 0; i < len; i++) {
        arr[i] = dist(gen);
    }

    switch (conf) {
        case 2:
            std::sort(arr.get(), arr.get() + (len / 3));
            break;
        case 3:
            std::sort(arr.get(), arr.get() + (len / 3) * 2);
            break;
        case 4:
            std::sort(arr.get(), arr.get() + len - 1);
            break;
        default:
            break;
    }

    return std::move(arr);
}

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
            size_t len = readArr<int32_t>(file, arr);

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
            size_t len = readArr<double>(file, arr);

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
        size_t len = readArr<int32_t>(file, arr);

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

void concurrentRun() {
    const uint32_t processorCount = std::thread::hardware_concurrency();

    auto threads = std::make_unique<MultiThreading::LinkedList<std::thread>>();
    auto algorithms = std::make_shared<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>();

    createAlgorithms(algorithms);

    for (uint32_t i = 0; i < processorCount; i++) {
        threads->push_front(std::make_unique<std::thread>(algorithmBenchmark, algorithms));
    }

    while (threads->getSize() != 0) {
        std::unique_ptr<std::thread> thread = threads->pop_back();
        if (thread && thread->joinable()) {
            thread->join();
        }
    }
}

void algorithmBenchmark(const std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>& algorithmQueue) {
    while (algorithmQueue->size() != 0) {
        auto algoBenchmark = algorithmQueue->pop();

        // timeout happened - queue likely empty
        if (algoBenchmark == nullptr) {
            return;
        }

        algoBenchmark->run();
    }
}

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

template <typename T>
void createBenchmarksFromFile(const std::filesystem::directory_entry & f, const std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>& algorithmQueue) {
    std::shared_ptr<T[]> arr;
    size_t len = readArr(f.path(), arr);

    algorithmQueue->push(std::make_unique<Sorting::HeapSort<T>>(arr.get(), len));
    algorithmQueue->push(std::make_unique<Sorting::InsertionSort<T>>(arr.get(), len));
    algorithmQueue->push(std::make_unique<Sorting::QuickSort<T>>(arr.get(), len));
    algorithmQueue->push(std::make_unique<Sorting::ShellSort<T>>(arr.get(), len));
}

template <typename T>
size_t readArr(const std::filesystem::path & f, std::shared_ptr<T[]>& ref) {
    std::fstream file;
    file.open(f);

    size_t len;
    std::string line;
    if (getline(file, line)) {
        len = std::stoi(line);
    } else {
       throw std::length_error("File is empty");
    }

    ref = std::shared_ptr<T[]>(new T[len]);
    for (int i = 0; i < len; i++) {
       if (!getline(file, line)) {
           throw std::range_error("wrong file format");
       }

       if (typeid(T) == typeid(int)) {
            ref[i] = std::stoi(line);
       } else if (typeid(T) == typeid(double)) {
            ref[i] = std::stod(line);
       }
    }

    return len;
}
