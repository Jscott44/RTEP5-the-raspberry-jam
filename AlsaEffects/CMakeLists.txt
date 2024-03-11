add_library(AlsaEffects STATIC AlsaBufferConverter.cpp EffectsManager.cpp AlsaListener.cpp ThreadBlocker.cpp)
target_include_directories(AlsaEffects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)