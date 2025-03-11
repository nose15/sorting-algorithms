#include <iostream>
#include "multithreading/linked_list/LinkedList.hpp"
#include "multithreading/blocking_queue/BlockingQueue.hpp"

int main() {
    auto* linkedList = new MultiThreading::LinkedList<int>();

    for (int i = 0; i < 5; i++) {
        std::unique_ptr<int> numPtr(new int(i));
        linkedList->push_front(std::move(numPtr));
    }

    for (int i = 0; i < 5; i++) {
        std::cout << *(linkedList->pop_back()) << std::endl;
    }

    auto* blockingQueue = new MultiThreading::BlockingQueue<int>();

    for (int i = 0; i < 5; i++) {
        blockingQueue->push(new int(i));
    }

    for (int i = 0; i < 5; i++) {
        std::cout << *(blockingQueue->pop()) << std::endl;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
