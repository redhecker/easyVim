cmake_minimum_required(VERSION 3.8)

project(temp)

# set the C++ standard and flags
set(CMAKE_CXX_STANDARD 11)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Windows 目前设定只需要通过测试即可
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Mac平台的配置，暂时没有测试过
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

# set options
option(TEST_OPTION "Test option" OFF) # default is OFF
if (DEFINED TEST_OPTION)
    message("Test option is defined: " ${TEST_OPTION})
    add_definitions(-DTEST_OPTION)
endif()

#src file
include_directories(src/modules)
add_subdirectory(src/modules bin)

# Unit test
if (TEST_OPTION)
    add_subdirectory(third_party/googletest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    add_subdirectory(src/test tests)
    enable_testing()
    add_test(NAME globalTest COMMAND tests)
endif()

find_package(fmt)
if (fmt_FOUND)
    message("fmt found")
    include_directories(${fmt_INCLUDE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${fmt_LIBRARIES})
else()
    message("fmt not found")
endif()

# generate library 生成动态链接库(名字include_hello可以更改)
add_library(include_hello SHARED ${PROJECT_SOURCE_DIR}/src/modules/lib.cpp)
install(TARGETS include_hello LIBRARY DESTINATION lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
install(FILES ${PROJECT_SOURCE_DIR}/src/include.hpp  DESTINATION include) 
