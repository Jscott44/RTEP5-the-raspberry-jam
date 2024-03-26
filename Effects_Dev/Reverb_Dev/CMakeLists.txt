cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory("sine_wave_gen/")
find_package(fir REQUIRED)

project ("RTEP-the-raspberry-jam")
add_executable(Reverb Reverb.cpp)
target_link_libraries(Reverb fir_static)
