#include <cstdint>

#ifndef ALSABUFFERCONVERTER_H
#define ALSABUFFERCONVERTER_H

class AlsaBufferConverter
{
public:
    AlsaBufferConverter();
    ~AlsaBufferConverter();

    int32_t getInt32FromBuffer(uint8_t* buffer);
    uint8_t* getBufferFromInt32(int32_t desired_value);
private:
    //uint8_t m_digitalBitsPerSample;
};

#endif