#include "include/AlsaBufferConverter.h"
#include <stdio.h>

/// @brief Object can be used to convert uint8 buffers into ChannelSample objects filled with int32s.
AlsaBufferConverter::AlsaBufferConverter()
    : m_leftBuffer(new uint8_t[BYTES_PER_SAMPLE]),
    m_rightBuffer(new uint8_t[BYTES_PER_SAMPLE])
{
    // Buffers initialsed are used when in getBuffer()
}

/// @brief Frees buffers associated with object.
AlsaBufferConverter::~AlsaBufferConverter()
{
    delete[] m_leftBuffer;
    m_leftBuffer = nullptr;

    delete[] m_rightBuffer;
    m_rightBuffer = nullptr;;
}

/// @brief Converts a buffer of int24s into usable values stored within a ChannelSamples object.
/// @param ret_samples RETURN. Fills channel samples with data from buffer.
/// @param buffer A buffer containing interleaved int24s.
void AlsaBufferConverter::getSamples(ChannelSamples* ret_samples, uint8_t* buffer)
{
    // Loop through all samples stored int the uint8 buffer
    for (unsigned int sampleIndex = 0; sampleIndex < FRAMES_PER_BUFFER; ++sampleIndex)
    {
        // Calculate the buffer index based on the bytes per sample and samples per frame
        unsigned int bufferIndex = sampleIndex * BYTES_PER_SAMPLE * SAMPLES_PER_FRAME;
    
        // Store calculated samples for each channel
        ret_samples->insertLeft(sampleIndex, getInt32FromBuffer(buffer + bufferIndex));
        ret_samples->insertRight(sampleIndex, getInt32FromBuffer(buffer + bufferIndex + BYTES_PER_SAMPLE));
    }
}

/// @brief Converts a ChannelSamples object into a buffer storing interleaved int24s.
/// @param ret_buffer RETURN. Fills buffer with data from samples object. Must be 3 * number of frames * number of channels long.
/// @param samples Object containing data that should be converted into an interleaved int24 buffer.
void AlsaBufferConverter::getBuffer(uint8_t* ret_buffer, ChannelSamples* samples)
{
    // Loop through all frames stored in structure
    for (unsigned int sampleIndex = 0; sampleIndex < samples->getFramesCount(); ++sampleIndex)
    {
        // For each frame, extract the sample and convert into int24 (in form of 3 uint8s)
        getBufferFromInt32(m_leftBuffer, samples->getLeftElement(sampleIndex));
        getBufferFromInt32(m_rightBuffer, samples->getRightElement(sampleIndex));
        
        // Calculate the buffer index based on the bytes per sample and samples per frame
        unsigned int bufferIndex = sampleIndex * BYTES_PER_SAMPLE * SAMPLES_PER_FRAME;

        // Store values into return buffer at correct index
        // Will store left channel at index sampleIndex + (0,1,2) and right channel at index sampleIndex + (3,4,5)
        for (int byteIndex = 0; byteIndex < BYTES_PER_SAMPLE; ++byteIndex)
        {
            ret_buffer[bufferIndex + byteIndex] = m_leftBuffer[byteIndex];
            ret_buffer[bufferIndex + byteIndex + BYTES_PER_SAMPLE] = m_rightBuffer[byteIndex];
        }
    }

}


/// @brief Converts buffer containing int24s into usable int32s.
/// @param buffer Contains int24 buffer that should be converted.
/// @return Int32 value equal to the int24 (including sign).
int32_t AlsaBufferConverter::getInt32FromBuffer(uint8_t* buffer)
{
    if (BYTES_PER_SAMPLE == 2)
    {
        int32_t retVal = ((buffer[0] << 24) | (buffer[1] << 16)) >> 16;
        return retVal;
    }
    else if (BYTES_PER_SAMPLE == 3)
    {
        // Example to understand procedure:
        // 0. Lets say int24 value ox 0x800000
        // 1. Shift int24 to end of the int32 (0x80000000)
        // 2. Shift int24 back 8 bits. This maintains the sign of the integer and fills the top byte based off the signed (0xFF800000)
        int32_t retVal = ((buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8)) >> 8;
        return retVal;
    }
    return 0;
}

/// @brief Converts int32 values int buffer containing int24s. Clips values if they are > MAX_INT_24 or < MIN_INT_24 before conversion.
/// @param ret_buffer RETURN. Buffer storing int24s. Must be at least 3 bytes long.
/// @param desired_value Int32 that should be converted into an int24 buffer
void AlsaBufferConverter::getBufferFromInt32(uint8_t* ret_buffer, int32_t desired_value)
{
    if (BYTES_PER_SAMPLE == 2)
    {
        if (desired_value < INT16_MIN)
        {
            desired_value = INT16_MIN;
        }
        else if (desired_value > INT16_MAX)
        {
            desired_value = INT16_MAX;
        }

        // Perform bitwise shifts to store relevant values in our return buffer
        ret_buffer[0] = desired_value >> 8;
        ret_buffer[1] = desired_value;
    }
    else if (BYTES_PER_SAMPLE == 3)
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
        ret_buffer[0] = desired_value >> 16;
        ret_buffer[1] = desired_value >> 8;
        ret_buffer[2] = desired_value;
    }
}











ChannelSamples::ChannelSamples(uint16_t num_of_frames)
{
    left = new int32_t[num_of_frames];
    right = new int32_t[num_of_frames];
    m_framesCount = num_of_frames;
}

ChannelSamples::~ChannelSamples()
{
    delete[] left;
    left = nullptr;

    delete[] right;
    right = nullptr;
}


void ChannelSamples::insertLeft(uint16_t index, int32_t value)
{
    left[index] = value;
}

void ChannelSamples::insertRight(uint16_t index, int32_t value)
{
    right[index] = value;
}

int32_t ChannelSamples::getLeftElement(uint16_t index)
{
    return left[index];
}

int32_t ChannelSamples::getRightElement(uint16_t index)
{
    return right[index];
}

uint16_t ChannelSamples::getFramesCount()
{
    return m_framesCount;
}