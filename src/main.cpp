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

void algorithmBenchmark(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue);
void createAlgorithms(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue);

template <typename T>
void createBenchmarksFromFile(const std::filesystem::directory_entry & f, std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue);

template <typename T>
size_t readIntArr(const std::filesystem::directory_entry & f, std::shared_ptr<T[]>& ref);

std::unique_ptr<Sorting::AlgorithmBenchmark> createFloatAlgorithm(const std::filesystem::directory_entry & f);
void concurrentRun();
void readCLIArgs(int argc, char** argv, std::unordered_map<std::string, std::string>& flags);

int main(int argc, char** argv) {
    std::unordered_map<std::string, std::string> flags;
    readCLIArgs(argc, argv, flags);
    std::ifstream resFile;

    try {
        if (flags.find("result") != flags.end()) {
            std::string fileName = flags["result"];
            if (fileName.empty()) throw std::invalid_argument("No file name specified");

            resFile = std::ifstream(fileName.c_str());
            if (!resFile.good()) throw std::invalid_argument("Wrong file name specified");
        }

        if (flags.find("auto") != flags.end()) {
            std::cout << "Running automatic benchmark..." << std::endl;
            concurrentRun();
        } else if (flags.find("file") != flags.end()) {
            std::string param = flags["file"];
            if (param.empty()) throw std::invalid_argument("No file name specified");
        }
    } catch (std::logic_error& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
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

void algorithmBenchmark(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue) {
    while (algorithmQueue->size() != 0) {
        auto algoBenchmark = algorithmQueue->pop();

        // timeout happened - queue likely empty
        if (algoBenchmark == nullptr) {
            return;
        }

        algoBenchmark->run();
    }
}

void createAlgorithms(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue) {
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
void createBenchmarksFromFile(const std::filesystem::directory_entry & f, std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue) {
    std::shared_ptr<T[]> arr;
    size_t len = readIntArr(f, arr);

    algorithmQueue->push(std::make_unique<Sorting::HeapSort<T>>(arr.get(), len));
    algorithmQueue->push(std::make_unique<Sorting::InsertionSort<T>>(arr.get(), len));
    algorithmQueue->push(std::make_unique<Sorting::QuickSort<T>>(arr.get(), len));
    algorithmQueue->push(std::make_unique<Sorting::ShellSort<T>>(arr.get(), len));
}

template <typename T>
size_t readIntArr(const std::filesystem::directory_entry & f, std::shared_ptr<T[]>& ref) {
    std::fstream file;
    file.open(f.path());

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
