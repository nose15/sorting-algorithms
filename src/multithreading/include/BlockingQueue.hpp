//
// Created by lukasz on 11.03.25.
//

#ifndef AIZO_1_BLOCKINGQUEUE_HPP
#define AIZO_1_BLOCKINGQUEUE_HPP

#include <cstdint>
#include <cstddef>
#include <thread>
#include <SpinningLock.hpp>
#include <LinkedList.hpp>


namespace MultiThreading {

    template<typename T>
    class BlockingQueue {
    private:
        LinkedList<T>* linkedList;
        SpinningLock* spinningLock;
    public:
        BlockingQueue();
        void push(std::unique_ptr<T> arg);
        size_t size();
        std::unique_ptr<T> pop();
        ~BlockingQueue();
    };

    template<typename T>
    size_t BlockingQueue<T>::size() {
        return linkedList->getSize();
    }

    template<typename T>
    BlockingQueue<T>::BlockingQueue() {
        linkedList = new LinkedList<T>();
        spinningLock = new SpinningLock();
    }

    template<typename T>
    BlockingQueue<T>::~BlockingQueue() {
        delete linkedList;
        delete spinningLock;
    }

    template<typename T>
    std::unique_ptr<T> BlockingQueue<T>::pop() {
        std::unique_ptr<T> ptr = nullptr;

        auto start = std::chrono::system_clock::now();
        auto elapsed = std::chrono::system_clock::now() - start;
        while (elapsed.count() < 100000) {
            spinningLock->lock();

            if (linkedList->getSize() > 0) {
                ptr = std::move(linkedList->pop_back());
                spinningLock->unlock();
                break;
            }

            spinningLock->unlock();
            elapsed = std::chrono::system_clock::now() - start;
            std::this_thread::yield();
        }

        return ptr;
    }

    template<typename T>
    void BlockingQueue<T>::push(std::unique_ptr<T> arg) {
        this->spinningLock->lock();
        linkedList->push_front(std::move(arg));
        spinningLock->unlock();
    }
} // MultiThreading

#endif //AIZO_1_BLOCKINGQUEUE_HPP
