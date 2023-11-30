cmake_minimum_required(VERSION 3.14)

project(prog)
include_directories($ENV{LLVM15I})
file(GLOB SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_directories(${PROJECT_NAME} PUBLIC $ENV{LLVM15L})
target_link_libraries(${PROJECT_NAME} LLVM-15)
