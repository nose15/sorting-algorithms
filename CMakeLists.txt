cmake_minimum_required(VERSION 3.28)
project(aizo_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(aizo_1 main.cpp
        sorting/sorting_algorithm/SortingAlgorithm.hpp
        sorting/insertion_sort/InsertionSort.hpp
        sorting/insertion_sort/InsertionSort.cpp
        sorting/heap_sort/HeapSort.cpp
        sorting/heap_sort/HeapSort.hpp
        sorting/shell_sort/ShellSort.cpp
        sorting/shell_sort/ShellSort.hpp
        sorting/sorting_algorithm/SortingAlgorithm.cpp
        sorting/quick_sort/QuickSort.cpp
        sorting/quick_sort/QuickSort.hpp
        multithreading/spinning_lock/SpinningLock.cpp
        multithreading/spinning_lock/SpinningLock.hpp
        multithreading/blocking_queue/BlockingQueue.hpp
        multithreading/linked_list/LinkedList.hpp
        multithreading/linked_list/Node.hpp)
