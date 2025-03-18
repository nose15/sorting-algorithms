#include <iostream>
#include <BlockingQueue.hpp>
#include <SortingAlgorithm.hpp>

void testAlgorithms(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::SortingAlgorithm<int32_t>>> algorithmQueue);
void createAlgorithms(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::SortingAlgorithm<int32_t>>> algorithmQueue);


int main() {
    auto threads = std::make_unique<MultiThreading::LinkedList<std::thread>>();
    auto algorithms = std::make_shared<MultiThreading::BlockingQueue<Sorting::SortingAlgorithm<int32_t>>>();
    createAlgorithms(algorithms);
    const uint32_t processorCount = std::thread::hardware_concurrency();


    for (uint32_t i = 0; i < processorCount; i++) {
        threads->push_front(std::make_unique<std::thread>(testAlgorithms, algorithms));
    }

    while (threads->getSize() != 0) {
        std::unique_ptr<std::thread> thread = threads->pop_back();
        if (thread && thread->joinable()) {
            thread->join();
        }
    }
}

void testAlgorithms(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::SortingAlgorithm<int32_t>>> algorithmQueue) {

}

void createAlgorithms(std::shared_ptr<MultiThreading::BlockingQueue<Sorting::SortingAlgorithm<int32_t>>> algorithmQueue) {

}