add_library(sorting
        Sorting.cpp
)

target_include_directories(sorting PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(sorting PUBLIC utils multithreading)