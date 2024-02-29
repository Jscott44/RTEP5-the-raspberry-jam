#include <cstdint>
#include <memory>

#ifndef ALSABUFFERCONVERTER_H
#define ALSABUFFERCONVERTER_H

class AlsaBufferConverter
{
public:
    AlsaBufferConverter();
    ~AlsaBufferConverter();

    std::unique_ptr<int32_t> getSamples(uint8_t* buffer);
    std::unique_ptr<uint8_t> getBuffer(int32_t* samples);

    const uint8_t getBytesPerSample() { return BYTES_PER_SAMPLE; };
    const uint16_t getSamplesPerBuffer() { return SAMPLES_PER_BUFFER; };
private:
    int32_t getInt32FromBuffer(uint8_t* buffer);
    uint8_t* getBufferFromInt32(int32_t desired_value);

    static const uint8_t BYTES_PER_SAMPLE = 3; // = 3; For 24 bit I2S messages
    static const uint16_t SAMPLES_PER_BUFFER = 44; // = 44; Buffer will fill every 1ms when ADC is transmitting at 44kHz
};

#endif