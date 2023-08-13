cmake_minimum_required(VERSION 3.24)
project(testTaskProgramOne)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external)

add_executable(testTaskProgramOne main.cpp src/input_data.cpp src/input_data.h src/data_synchronization.cpp src/data_synchronization.h src/processing_data.cpp src/processing_data.h)

target_link_libraries(testTaskProgramOne PRIVATE Boost::asio)


