#include "AlsaBufferConverter.h"

AlsaBufferConverter::AlsaBufferConverter()
{

}

AlsaBufferConverter::~AlsaBufferConverter()
{
    
}

/// @brief Converts signed int buffer into signed 32 bit integer
/// @param buffer Buffer containing signed integer obtained by ALSA
/// @return Signed 32 bit integer that can be used in C++
int32_t AlsaBufferConverter::getInt32FromBuffer(uint8_t* buffer)
{
    // 0. Start with 0x00000000 and 0x800000
    // 1. Shift 24 bits to end of 32 bit integer (0x80000000)
    // 2. Shift 24 bits back 8 bits. This continues the signing of the integer and fills the top byte based off the signed (0xFF800000)
    int32_t retVal = ((buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8)) >> 8;
    return retVal;
}

/// @brief Converts signed 32 bit integer into 3 byte buffer containing the values for a signed 24 int value
/// @param buffer int32 value that should be converted into signed 24 int buffer
/// @return buffer containing 24 bit signed value stored as uint8s
uint8_t* AlsaBufferConverter::getBufferFromInt32(int32_t desired_value)
{
    // Ensure desired_value is not greater than the maximum or less that the minimum signed 24 bit values
    //If they are, alter value to be max/min
    const int32_t MAX_INT_24 = 0x7FFFFF;
    const int32_t MIN_INT_24 = 0Xff800000;

    if (desired_value < MIN_INT_24)
    {
        desired_value = MIN_INT_24;
    }
    else if (desired_value > MAX_INT_24)
    {
        desired_value = MAX_INT_24;
    }
    
    // Perform bitwise shifts to store relevant values in our return buffer
    uint8_t retBuffer[3];
    retBuffer[0] = desired_value >> 16;
    retBuffer[1] = desired_value >> 8;
    retBuffer[2] = desired_value;

    return retBuffer;
}