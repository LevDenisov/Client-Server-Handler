cmake_minimum_required(VERSION 3.24)
project(testTaskProgramTwo)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)

add_executable(testTaskProgramTwo main.cpp)

target_link_libraries(testTaskProgramTwo PRIVATE Boost::asio)
