#include "include/AlsaBufferConverter.h"
#include <stdio.h>

/// @brief Object can be used to convert uint8 buffers into ChannelSample objects filled with int32s.
AlsaBufferConverter::AlsaBufferConverter(eEndianness endian, uint8_t bytes_per_sample, uint16_t frames_per_buffer)
    : ENDIANNESS(endian),
    BYTES_PER_SAMPLE(bytes_per_sample),
    FRAMES_PER_BUFFER(frames_per_buffer),
    m_leftBuffer(new uint8_t[BYTES_PER_SAMPLE]),
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

/// @brief Converts a buffer of ints into usable values stored within a ChannelSamples object. Expected input INT type depends on object constructor arguments.
/// @param ret_samples RETURN. Fills channel samples with data from buffer.
/// @param buffer A buffer containing interleaved ints.
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

/// @brief Converts a ChannelSamples object into a buffer storing interleaved INTs. Output INT type depends on object constructor arguments.
/// @param ret_buffer RETURN. Fills buffer with data from samples object. Must be bytes per sample * number of frames * 2 (number of channels) long.
/// @param samples Object containing data that should be converted into an interleaved INT buffer.
void AlsaBufferConverter::getBuffer(uint8_t* ret_buffer, ChannelSamples* samples)
{
    // Loop through all frames stored in structure
    for (unsigned int sampleIndex = 0; sampleIndex < FRAMES_PER_BUFFER; ++sampleIndex)
    {
        // For each frame, extract the sample and convert into buffer equivalent
        getBufferFromInt32(m_leftBuffer, samples->getLeftElement(sampleIndex));
        getBufferFromInt32(m_rightBuffer, samples->getRightElement(sampleIndex));
        
        // Calculate the buffer index based on the bytes per sample and samples per frame
        unsigned int bufferIndex = sampleIndex * BYTES_PER_SAMPLE * SAMPLES_PER_FRAME;

        // Store values into return buffer at correct index
        for (int byteIndex = 0; byteIndex < BYTES_PER_SAMPLE; ++byteIndex)
        {
            ret_buffer[bufferIndex + byteIndex] = m_leftBuffer[byteIndex];
            ret_buffer[bufferIndex + byteIndex + BYTES_PER_SAMPLE] = m_rightBuffer[byteIndex];
        }
    }

}


/// @brief Converts buffer containing int samples into usable INT32s. Expected input INT type depends on object constructor arguments.
/// @param buffer Contains int buffer that should be converted.
/// @return INT32 value equal to the INT sample received (including sign).
int32_t AlsaBufferConverter::getInt32FromBuffer(uint8_t* buffer)
{
    int32_t retVal = 0;
    if (BYTES_PER_SAMPLE == 2)
    {
        switch (ENDIANNESS)
        {
        case eBIG:
            retVal = ((buffer[0] << 24) | (buffer[1] << 16)) >> 16;
            break;
        case eLITTLE:
            retVal = ((buffer[1] << 24) | (buffer[0] << 16)) >> 16;
            break;
        default:
            fprintf(stderr, "Invalid endiannes: %d", ENDIANNESS);
            break;
        }
    }
    else if (BYTES_PER_SAMPLE == 3)
    {
        // Example to understand procedure:
        // 0. Lets say int24 value 0x800000
        // 1. Shift int24 to end of the int32 (0x80000000)
        // 2. Shift int24 back 8 bits. This maintains the sign of the integer and fills the top byte based off the signed (0xFF800000)
        switch (ENDIANNESS)
        {
        case eBIG:
            retVal = ((buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8)) >> 8;
            break;
        case eLITTLE:
            retVal = ((buffer[2] << 24) | (buffer[1] << 16) | (buffer[0] << 8)) >> 8;
            break;
        default:
            fprintf(stderr, "Invalid endiannes: %d", ENDIANNESS);
            break;
        }
    }
    return retVal;
}

/// @brief Converts int32 values int buffer containing INT samples. Clips values if they are larger than the max INT value or smaller than the min INT value for their type. Output INT type depends on object constructor arguments.
/// @param ret_buffer RETURN. Buffer storing INT samples. Must be long enough to store return value (2 bytes for INT16s, 3 bytes for INT24s).
/// @param desired_value Int32 that should be converted into a buffer containing INT samples.
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

        switch (ENDIANNESS)
        {
        case eBIG:
            // Perform bitwise shifts to store relevant values in our return buffer
            ret_buffer[0] = desired_value >> 8;
            ret_buffer[1] = desired_value;
            break;
        case eLITTLE:
            // Perform bitwise shifts to store relevant values in our return buffer
            ret_buffer[1] = desired_value >> 8;
            ret_buffer[0] = desired_value;
            break;
        default:
            fprintf(stderr, "Invalid endiannes: %d", ENDIANNESS);
            break;
        }
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

        switch (ENDIANNESS)
        {
        case eBIG:
            // Perform bitwise shifts to store relevant values in our return buffer
            ret_buffer[0] = desired_value >> 16;
            ret_buffer[1] = desired_value >> 8;
            ret_buffer[2] = desired_value;
            break;
        case eLITTLE:
            // Perform bitwise shifts to store relevant values in our return buffer
            ret_buffer[2] = desired_value >> 16;
            ret_buffer[1] = desired_value >> 8;
            ret_buffer[0] = desired_value;
            break;
        default:
            fprintf(stderr, "Invalid endiannes: %d", ENDIANNESS);
            break;
        }
    }
}










/// @brief Object stores samples obtained in their respective channel arrays.
/// @param num_of_frames The number of frames being received.
ChannelSamples::ChannelSamples(uint16_t num_of_frames)
{
    // Allocate memory on heap to store samples
    left = new int32_t[num_of_frames];
    right = new int32_t[num_of_frames];

    // Store frame count for future use
    m_framesCount = num_of_frames;
}

/// @brief Frees memory allocated.
ChannelSamples::~ChannelSamples()
{
    delete[] left;
    left = nullptr;

    delete[] right;
    right = nullptr;
}

/// @brief Inserts sample into left array at given index.
/// @param index Index the sample should be stored at.
/// @param value Sample that should be stored.
void ChannelSamples::insertLeft(uint16_t index, int32_t value)
{
    left[index] = value;
}

/// @brief Inserts sample into right array at given index.
/// @param index Index the sample should be stored at.
/// @param value Sample that should be stored.
void ChannelSamples::insertRight(uint16_t index, int32_t value)
{
    right[index] = value;
}

/// @brief Returns sample stored in left arry at given index.
/// @param index Index the sample should be obtained from.
/// @return The sample stored at the given index.
int32_t ChannelSamples::getLeftElement(uint16_t index)
{
    return left[index];
}

/// @brief Returns sample stored in right arry at given index.
/// @param index Index the sample should be obtained from.
/// @return The sample stored at the given index.
int32_t ChannelSamples::getRightElement(uint16_t index)
{
    return right[index];
}

/// @brief Returns the frame count of this object. Cannot store more samples per channel than this value.
/// @return Number of frames.
uint16_t ChannelSamples::getFramesCount()
{
    return m_framesCount;
}