add_library(sorting
        HeapSort.cpp
        InsertionSort.cpp
        QuickSort.cpp
        ShellSort.cpp
        SortingAlgorithm.cpp
)

target_include_directories(sorting PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)