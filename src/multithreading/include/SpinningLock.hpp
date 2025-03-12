//
// Created by lukasz on 11.03.25.
//

#ifndef AIZO_1_SPINNINGLOCK_HPP
#define AIZO_1_SPINNINGLOCK_HPP

#include <atomic>

namespace MultiThreading {
    class SpinningLock {
    private:
        std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;
    public:
        void lock();
        void unlock();
    };

} // MultiThreading

#endif //AIZO_1_SPINNINGLOCK_HPP
