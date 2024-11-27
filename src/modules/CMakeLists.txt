set(BINARY ${CMAKE_PROJECT_NAME})
 
# 1
# add_executable(ExampleProject main.cpp file1.cpp file1.h)
 
# 2
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)
set(SOURCES ${SOURCES})

find_package(fmt)
if (fmt_FOUND)
    add_executable(${BINARY} ${SOURCES})
endif()

# 为了让单元测试的时候src下的代码能被作为静态链接库使用
add_library(${BINARY}_lib STATIC ${SOURCES})