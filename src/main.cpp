#include <iostream>
#include <BlockingQueue.hpp>
#include <SortingAlgorithm.hpp>
#include <filesystem>
#include <fstream>
#include "HeapSort.hpp"

void algorithmBenchmark(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue);
void createAlgorithms(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue);
std::unique_ptr<Sorting::AlgorithmBenchmark> createIntAlgorithm(const std::filesystem::directory_entry & f);
std::unique_ptr<Sorting::AlgorithmBenchmark> createFloatAlgorithm(const std::filesystem::directory_entry & f);

int main() {
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

        std::cout << datatype << std::endl;
        if (datatype == "int") {
            auto alg = createIntAlgorithm(f);
            algorithmQueue->push(std::move(alg));
        }
        else if (datatype == "flo") {
            continue;
            algorithmQueue->push(createFloatAlgorithm(f));
        }
    }
}

std::unique_ptr<Sorting::AlgorithmBenchmark> createIntAlgorithm(const std::filesystem::directory_entry & f) {
    std::fstream file;
    file.open(f.path());

    int32_t len;
    std::string line;
    if (getline(file, line)) {
        len = std::stoi(line);
    } else {
       throw std::length_error("File is empty");
    }

    auto * arr = new int32_t[len];
    for (int i = 0; i < len; i++) {
       if (!getline(file, line)) {
           throw std::range_error("wrong file format");
       }

       arr[i] = std::stoi(line);
       std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return std::make_unique<Sorting::HeapSort<int32_t>>(arr, len);
}

std::unique_ptr<Sorting::AlgorithmBenchmark> createFloatAlgorithm(const std::filesystem::directory_entry & f) {

}
