cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory("sine_wave_gen/")

project ("RTEP-the-raspberry-jam")
add_executable(Distortion Distortion.cpp)
