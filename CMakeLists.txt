cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(lab1 main.cpp)
add_executable(bonus bonus.cpp)
target_link_libraries(lab1 ${OpenCV_LIBS})
target_link_libraries(bonus ${OpenCV_LIBS})