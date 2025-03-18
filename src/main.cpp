#include <iostream>
#include <BlockingQueue.hpp>
#include <SortingAlgorithm.hpp>

void algorithmBenchmark(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue);
void createAlgorithms(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue);

int main() {
    auto threads = std::make_unique<MultiThreading::LinkedList<std::thread>>();
    auto algorithms = std::make_shared<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>>();
    createAlgorithms(algorithms);
    const uint32_t processorCount = std::thread::hardware_concurrency();

    // load arrays from files
    // create each sorting algorithm with each array
    // push the algorithm into a queue
    // run threads
    // repeat for doubles

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
        if (algoBenchmark == nullptr) break;

        algoBenchmark->run();
    }
}

void createAlgorithms(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::AlgorithmBenchmark>> algorithmQueue) {

}