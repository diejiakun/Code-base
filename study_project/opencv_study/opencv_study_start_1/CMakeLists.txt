cmake_minimum_required(VERSION 3.22.1)
project(OpenCVExample)

find_package(OpenCV REQUIRED)

add_executable(OpenCVExample geometric_transformations_of_images.cpp)

target_link_libraries(OpenCVExample ${OpenCV_LIBS})