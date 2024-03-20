cmake_minimum_required(VERSION 3.27)
project(CLF_CBF_learn)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR ${PROJECT_SOURCE_DIR}/include/opencv/install)
find_package(OpenCV REQUIRED)
#set(osqp_DIR ${PROJECT_SOURCE_DIR}/include/osqp/install/lib/cmake/osqp)
find_package(osqp REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${osqp_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include/osqp/install/include/)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(CLF_CBF_learn main.cpp
        dynamic.cpp
        dynamic.h
        display.cpp
        display.h)
target_link_libraries(CLF_CBF_learn ${OpenCV_LIBS})
target_link_libraries(CLF_CBF_learn osqp::osqp)