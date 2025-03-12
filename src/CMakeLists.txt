add_subdirectory(multithreading)
add_subdirectory(sorting)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE multithreading sorting)