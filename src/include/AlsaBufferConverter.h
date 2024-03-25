#ifndef ALSABUFFERCONVERTER_H
#define ALSABUFFERCONVERTER_H

#include <cstdint>
#include <vector>
#include "DataFormat.h"

class ChannelSamples
{
public:
    ChannelSamples(uint16_t num_of_frames);
    ~ChannelSamples();
    void insertLeft(uint16_t index, int32_t value);
    void insertRight(uint16_t index, int32_t value);
    int32_t getLeftElement(uint16_t index);
    int32_t getRightElement(uint16_t index);
    uint16_t getFramesCount();
private:
    int32_t* left;
    int32_t* right;
    uint16_t m_framesCount;
};

class AlsaBufferConverter
{
public:
    AlsaBufferConverter(eEndianness endian, uint8_t bytes_per_sample, uint16_t frames_per_buffer);
    ~AlsaBufferConverter();

    void getSamples(ChannelSamples* ret_samples, uint8_t* buffer);

    void getBuffer(uint8_t* ret_buffer, ChannelSamples* samples);

    const uint8_t getBytesPerSample() { return BYTES_PER_SAMPLE; };
    const uint16_t getSamplesPerFrame() { return SAMPLES_PER_FRAME; };
    const uint16_t getFramesPerBuffer() { return FRAMES_PER_BUFFER; };
private:
    int32_t getInt32FromBuffer(uint8_t* buffer);
    void getBufferFromInt32(uint8_t* ret_buffer, int32_t desired_value);

    const eEndianness ENDIANNESS; // eBig or eLittle
    const uint8_t BYTES_PER_SAMPLE; // = 3 OR 2 (INT24 or INT16)
    const uint8_t SAMPLES_PER_FRAME = 2; // = 2; Stereo
    const uint16_t FRAMES_PER_BUFFER; // Varies

    uint8_t* m_leftBuffer;
    uint8_t* m_rightBuffer;
};

#endif
