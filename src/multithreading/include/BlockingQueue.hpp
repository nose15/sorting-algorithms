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
        void push(T* arg);
        std::unique_ptr<T> pop();
        ~BlockingQueue();
    };

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
        std::unique_ptr<T> ptr;

        while (true) {
            spinningLock->lock();

            if (linkedList->getSize() > 0) {
                ptr = std::move(linkedList->pop_back());
                spinningLock->unlock();
                break;
            }

            spinningLock->unlock();
            std::this_thread::yield();
        }

        return ptr;
    }

    template<typename T>
    void BlockingQueue<T>::push(T* arg) {
        spinningLock->lock();
        std::unique_ptr<T> ptr(arg);
        linkedList->push_front(std::move(ptr));
        spinningLock->unlock();
    }
} // MultiThreading

#endif //AIZO_1_BLOCKINGQUEUE_HPP
