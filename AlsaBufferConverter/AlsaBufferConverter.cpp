#include "AlsaBufferConverter.h"

AlsaBufferConverter::AlsaBufferConverter()
{

}

AlsaBufferConverter::~AlsaBufferConverter()
{
    
}

/// @brief Get int32 sample array containing the equivalent int32 values as the int24 values that were stored in a uint8 buffer.
/// @param Uint8 buffer containing the int24 data that should be converted into usable int32s
/// @return Unique ptr to an array storing int32 equivalent values
std::unique_ptr<int32_t> AlsaBufferConverter::getSamples(uint8_t* buffer)
{
    // Store on heap as unique pointer will be passed around
    std::unique_ptr<int32_t> retSamples(new int32_t[SAMPLES_PER_BUFFER]);
    
    // Loop through all samples stored int the uint8 buffer
    for (unsigned int sampleIndex = 0; sampleIndex < SAMPLES_PER_BUFFER; ++sampleIndex)
    {
        // Calculate the buffer index based on the bytes per sample
        unsigned int bufferIndex = sampleIndex * BYTES_PER_SAMPLE;

        // Store calculated samples in array
        retSamples.get()[sampleIndex] = getInt32FromBuffer(buffer + bufferIndex);
    }

    return retSamples;
}

/// @brief Get buffer containing int24s stored as uint8s that are equivalent to the original sample values.
/// @param Int32 array containing samples that should be converted.
/// @return Unique ptr to the buffer. If the sample is greater/less than the max/min of int24s, the returned value is capped.
std::unique_ptr<uint8_t> AlsaBufferConverter::getBuffer(int32_t* samples)
{
    // Store on heap as unique pointer will be passed around
    std::unique_ptr<uint8_t> retBuffer(new uint8_t[BYTES_PER_SAMPLE * SAMPLES_PER_BUFFER]);

    // Loop through all int32 samples
    for (unsigned int sampleIndex = 0; sampleIndex < SAMPLES_PER_BUFFER; ++sampleIndex)
    {
        // For each sample, obtain the uint8 buffer equivalent
        uint8_t* functionReturn = getBufferFromInt32(samples[sampleIndex]);

        // Store values into return buffer at correct index
        unsigned int rawBytesIndex = sampleIndex * BYTES_PER_SAMPLE;
        for (int byteIndex = 0; byteIndex < BYTES_PER_SAMPLE; ++byteIndex)
        {
            retBuffer.get()[rawBytesIndex + byteIndex] = functionReturn[byteIndex];
        }
    }

    return retBuffer;
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