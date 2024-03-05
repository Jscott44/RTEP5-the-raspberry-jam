add_library(AlsaEffects STATIC AlsaBufferConverter.cpp EffectsManager.cpp AlsaEffects.cpp SafeQueue.cpp)
target_include_directories(AlsaEffects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)