project(Google_tests)


set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})



add_executable(list_test TestList.cpp)
target_link_libraries(list_test gtest gtest_main)

add_executable(vector_test TestVector.cpp)
target_link_libraries(vector_test gtest gtest_main)

add_executable(queue_test TestQueue.cpp)
target_link_libraries(queue_test gtest gtest_main)

add_executable(map_test TestMap.cpp)
target_link_libraries(map_test gtest gtest_main)

add_executable(stack_test TestStack.cpp)
target_link_libraries(stack_test gtest gtest_main)
