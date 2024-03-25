cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS  "-pthread")


project ("RTEP-the-raspberry-jam")
add_subdirectory(AlsaEffects)
add_subdirectory(test)

add_executable(rpj main.cpp)

target_link_libraries(rpj PUBLIC AlsaEffects)

find_package(ALSA REQUIRED)
if (ALSA_FOUND)
	include_directories(${ALSA_INCLUDE_DIRS})
	target_link_libraries(rpj PUBLIC ${ALSA_LIBRARIES})
endif(ALSA_FOUND)

enable_testing()
add_test(NAME MyTest COMMAND Test)
