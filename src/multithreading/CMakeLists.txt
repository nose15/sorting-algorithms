add_library(multithreading
        SpinningLock.cpp
)

target_include_directories(multithreading PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)