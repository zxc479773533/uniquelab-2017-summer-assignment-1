# 标准测试
cmake_minimum_required (VERSION 2.8.11)
project (heapsort_test)

add_subdirectory(googletest ${CMAKE_BINARY_DIR}/googletest)

add_executable(set_test set_test.cpp)
add_executable(pq_test pq_test.cpp)

add_library(priority_queue priority_queue.cpp)

add_library(set set.cpp)

target_link_libraries(set_test set gtest_main)
target_link_libraries(pq_test priority_queue gtest_main)

# 这是一个CMake的范本
project(ass)
# 编译

add_library(bst binary_search_tree.cpp)

add_library(avl AVL_tree.cpp)
# 生成可执行文件

add_executable(tbst test_BST.cpp)

add_executable(tavl test_AVL.cpp)
# 链接编译文件与可执行文件

target_link_libraries(tbst bst)

target_link_libraries(tavl avl)