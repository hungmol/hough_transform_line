cmake_minimum_required(VERSION 3.10)

project(HoughTransformLine)
set(CMAKE_CXX_STANDARD 17)


set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/HoughTransformLine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HoughTransformLine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.h
    )

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${SRC})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} -lstdc++fs)
    