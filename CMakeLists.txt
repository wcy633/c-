cmake_minimum_required(VERSION 3.11)
project(class2 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(cmake_learn
    tools/main.cpp
    tools/image_source.cpp
    tools/algorithm.cpp
    tools/color-range.cpp
    tools/pid_task.cpp
    tools/contour_task.cpp
    tools/camera.cpp
)

target_include_directories(cmake_learn PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/tools
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(cmake_learn PRIVATE ${OpenCV_LIBS})