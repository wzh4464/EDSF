cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_NAME EDSF)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
FIND_PACKAGE(OpenCV REQUIRED)

file(GLOB EDSF_header src)
file(GLOB EDSF_sources src/*.cpp)

add_executable(edsf main.cpp ${EDSF_sources})
target_include_directories(edsf PUBLIC ${OpenCV_INCLUDE_DIRS} ${EDSF_header})
target_link_libraries(edsf ${OpenCV_LIBS})
