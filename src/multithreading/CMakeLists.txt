add_library(multithreading
        SpinningLock.cpp
        Multithreading.cpp
)

target_include_directories(multithreading PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(multithreading PRIVATE utils)