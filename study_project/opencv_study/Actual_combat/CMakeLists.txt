cmake_minimum_required(VERSION 3.22.1)
project(OpenCVExample)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 OpenCV 库
find_package(OpenCV REQUIRED)

# 输出找到的 OpenCV 版本信息，方便调试
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# 包含 OpenCV 头文件目录
include_directories(${OpenCV_INCLUDE_DIRS})

# 添加可执行文件
add_executable(OpenCVExample optical_flow_calculations.cpp)

# 链接 OpenCV 库
target_link_libraries(OpenCVExample ${OpenCV_LIBS})