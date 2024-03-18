#include <cstdint>
#include <vector>

#ifndef ALSABUFFERCONVERTER_H
#define ALSABUFFERCONVERTER_H

class ChannelSamples
{
public:
    ChannelSamples2(uint16_t num_of_frames);
    ~ChannelSamples2();
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
    AlsaBufferConverter();
    ~AlsaBufferConverter();

    //ChannelSamples getSamples(uint8_t* buffer);
    void getSamples(ChannelSamples ret_samples, uint8_t* buffer);

    //std::unique_ptr<uint8_t> getBuffer(ChannelSamples samples);
    void getBuffer(uint8_t* ret_buffer, ChannelSamples samples);

    const uint8_t getBytesPerSample() { return BYTES_PER_SAMPLE; };
    const uint16_t getSamplesPerFrame() { return SAMPLES_PER_FRAME; };
    const uint16_t getFramesPerBuffer() { return FRAMES_PER_BUFFER; };
private:
    int32_t getInt32FromBuffer(uint8_t* buffer);
    //std::unique_ptr<uint8_t> getBufferFromInt32(int32_t desired_value);
    void getBufferFromInt32(uint8_t* ret_buffer, int32_t desired_value);

    uint8_t* m_leftBuffer;
    uint8_t* m_rightBuffer;

    const uint8_t BYTES_PER_SAMPLE = 3; // = 3; For 24 bit I2S messages
    const uint8_t SAMPLES_PER_FRAME = 2; // = 2; Only using right and left channels
    const uint16_t FRAMES_PER_BUFFER = 44; // = 44; Buffer will fill every 1ms when ADC is transmitting at 44kHz
};

#endif