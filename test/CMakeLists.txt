include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY  https://github.com/google/googletest.git
        GIT_TAG         release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
add_executable(test
        sorting/HeapSortTest.cpp
        sorting/InsertionSortTest.cpp
)

target_link_libraries(GTest::GTest INTERFACE gtest_main)
target_link_libraries(test PRIVATE GTest::GTest sorting)

add_test(NAME TestHeapSort COMMAND TestHeapSort WORKING_DIRECTORY sorting/HeapSortTest.cpp)
add_test(NAME TestInsertionSort COMMAND TestInsertionSort WORKING_DIRECTORY sorting/InsertionSortTest.cpp)
