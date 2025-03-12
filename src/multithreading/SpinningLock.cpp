//
// Created by lukasz on 11.03.25.
//

#include <thread>
#include <SpinningLock.hpp>

namespace MultiThreading {
    void SpinningLock::lock() {
        while (lock_flag.test_and_set(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
    }

    void SpinningLock::unlock() {
        lock_flag.clear(std::memory_order_release);
    }
} // MultiThreading