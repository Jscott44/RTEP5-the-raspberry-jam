#include "include/AlsaBufferConverter.h"

AlsaBufferConverter::AlsaBufferConverter()
{

}

AlsaBufferConverter::~AlsaBufferConverter()
{
    
}

/// @brief Get object containing the equivalent int32 values as the int24 values that were stored in a uint8 buffer for each channel (left and right).
/// @param Uint8 buffer containing the int24 data that should be converted into usable int32s
/// @return ChannelSamples object containing int32 value equivalents for each channel.
ChannelSamples AlsaBufferConverter::getSamples(uint8_t* buffer)
{
    ChannelSamples retObj(FRAMES_PER_BUFFER);
    
    // Loop through all samples stored int the uint8 buffer
    for (unsigned int sampleIndex = 0; sampleIndex < FRAMES_PER_BUFFER; ++sampleIndex)
    {
        // Calculate the buffer index based on the bytes per sample and samples per frame
        unsigned int bufferIndex = sampleIndex * BYTES_PER_SAMPLE * SAMPLES_PER_FRAME;

        // Store calculated samples for each channel
        retObj.appendLeft(getInt32FromBuffer(buffer + bufferIndex));
        retObj.appendRight(getInt32FromBuffer(buffer + bufferIndex + BYTES_PER_SAMPLE));
    }

    //return retSamples;
    return retObj;
}

/// @brief Get buffer containing int24s stored as uint8s that are equivalent to the original sample values.
/// @param Int32 array containing samples that should be converted.
/// @return Unique ptr to the buffer. If the sample is greater/less than the max/min of int24s, the returned value is capped.
std::unique_ptr<uint8_t> AlsaBufferConverter::getBuffer(ChannelSamples samples)
{
    // Store on heap as unique pointer will be passed around
    std::unique_ptr<uint8_t> retBuffer(new uint8_t[BYTES_PER_SAMPLE * SAMPLES_PER_FRAME * FRAMES_PER_BUFFER]);

    // Loop through all int32 samples
    for (unsigned int sampleIndex = 0; sampleIndex < FRAMES_PER_BUFFER; ++sampleIndex)
    {
        // For each sample, obtain the uint8 buffer equivalent
        std::unique_ptr<uint8_t> leftBuffer = getBufferFromInt32(samples.getLeftElement(sampleIndex));
        std::unique_ptr<uint8_t> rightBuffer = getBufferFromInt32(samples.getRightElement(sampleIndex));

        // Store values into return buffer at correct index
        unsigned int rawBytesIndex = sampleIndex * BYTES_PER_SAMPLE * SAMPLES_PER_FRAME;
        for (int byteIndex = 0; byteIndex < BYTES_PER_SAMPLE; ++byteIndex)
        {
            retBuffer.get()[rawBytesIndex + byteIndex] = leftBuffer.get()[byteIndex];
            retBuffer.get()[rawBytesIndex + byteIndex + BYTES_PER_SAMPLE] = rightBuffer.get()[byteIndex];
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
/// @return Unique ptr to buffer containing 24 bit signed value stored as uint8s
std::unique_ptr<uint8_t> AlsaBufferConverter::getBufferFromInt32(int32_t desired_value)
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
    std::unique_ptr<uint8_t> retBuffer(new uint8_t[3]);
    retBuffer.get()[0] = desired_value >> 16;
    retBuffer.get()[1] = desired_value >> 8;
    retBuffer.get()[2] = desired_value;

    return retBuffer;
}










/// @brief Creates object storing samples for each channel. 
/// @param num_of_frames The number of frames that should be stored (each channel stores this many samples)
ChannelSamples::ChannelSamples(uint16_t num_of_frames)
    : m_framesCount(num_of_frames)
{
    // Reserve memory once so that the program does not need to constantly find and area large enough to store all values
    left.reserve(num_of_frames);
    right.reserve(num_of_frames);
}

uint16_t ChannelSamples::getFramesCount()
{
    return m_framesCount;
}

/// @brief Appends value onto the end of the left channel
/// @param value that should be appended
void ChannelSamples::appendLeft(int32_t value)
{
    left.push_back(value);
    return;
}

/// @brief Appends value onto the end of the right channel
/// @param value that should be appended
void ChannelSamples::appendRight(int32_t value)
{
    right.push_back(value);
    return;
}

/// @brief Returns the value that has been stored in the left channel container for the given index
/// @param index desired index of value
/// @return The element that has been stored for the given index
int32_t ChannelSamples::getLeftElement(uint16_t index)
{
    return left[index];
}

/// @brief Returns the value that has been stored in the right channel container for the given index
/// @param index desired index of value
/// @return The element that has been stored for the given index
int32_t ChannelSamples::getRightElement(uint16_t index)
{
    return right[index];
}