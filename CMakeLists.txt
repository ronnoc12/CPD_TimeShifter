cmake_minimum_required(VERSION 3.5)
project(CPDProject CXX)

#require a C++14 compiler for all targets 
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# configure Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Widgets Core Test REQUIRED)

add_executable(TimeShifter time_Shifter.cpp outputWindow.cpp outputWindow.hpp)

TARGET_LINK_LIBRARIES(TimeShifter ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(TimeShifter Qt5::Widgets)
