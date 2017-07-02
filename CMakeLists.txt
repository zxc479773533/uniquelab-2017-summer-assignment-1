project(ass)
# 这是一个CMake的范本
add_library(set set.cpp) #编译
add_library(pq priority_queue.cpp) #编译
add_executable(tt test.cpp) #生成可执行文件
target_link_libraries(tt pq set) #链接前两个文件至可执行文件