#include <cstdint>
#include <iostream>
#include "AlsaBufferConverter.h"

int main()
{
    const size_t numOfHexValues = 5;
    const size_t numOfBytes = 3 * numOfHexValues;

    //uint8_t buf[numOfHexValues][3] = {{0x7F, 0xFF, 0xFF},{0x40, 0x00, 0x00},{0x00, 0x00, 0x00},{0xc0, 0x00, 0x00},{0x80, 0x00, 0x00}};
    uint8_t buf[numOfBytes] = { 0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 };

    int32_t val;

    AlsaBufferConverter test;

    for (int index = 0; index < numOfBytes; index+=3)
    {
        std::cout << "Int24 to Int32" << std::endl;

        val = test.getInt32FromBuffer(buf+index);

        std::cout << std::dec << val << std::endl;
        std::cout << std::hex << val << "\n" << std::endl;

        std::cout << "Int32 to Int24" << std::endl;

        uint8_t* valBuf = test.getBufferFromInt32(val);
        printf("%02X%02X%02X \n\n\n", valBuf[0], valBuf[1], valBuf[2]);
    }
}