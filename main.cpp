#include <cstdint>
#include <iostream>
#include "AlsaBufferConverter.h"

int main()
{
    const size_t numOfValues = 5;

    uint8_t buf[numOfValues][3] = {{0x7F, 0xFF, 0xFF},{0x40, 0x00, 0x00},{0x00, 0x00, 0x00},{0xc0, 0x00, 0x00},{0x80, 0x00, 0x00}};

    int32_t val;

    AlsaBufferConverter test;

    for (int index = 0; index < numOfValues; index++)
    {
        val = test.getInt32FromBuffer(buf[index]);

        std::cout << std::dec << val << std::endl;
        std::cout << std::hex << val << "\n" << std::endl;
    }
}