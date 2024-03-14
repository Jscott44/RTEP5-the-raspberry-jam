add_library(AlsaPcmCapture STATIC AlsaPcmCapture.cpp)
target_include_directories(AlsaPcmCapture PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
