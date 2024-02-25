cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("RTEP-the-raspberry-jam")

add_subdirectory(AlsaBufferConverter)
add_executable(rpj main.cpp)
target_link_libraries(rpj PUBLIC AlsaBufferConverter)