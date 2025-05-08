cmake_minimum_required(VERSION 3.22.1)
project(OpenCVExample)

find_package(OpenCV REQUIRED)

add_executable(OpenCVExample contour_detection.cpp)

target_link_libraries(OpenCVExample ${OpenCV_LIBS})