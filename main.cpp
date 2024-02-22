#include <cstdint>
#include <iostream>

int main()
{
    const size_t numOfValues = 5;

    uint8_t buf[numOfValues][3] = {{0x7F, 0xFF, 0xFF},{0x40, 0x00, 0x00},{0x00, 0x00, 0x00},{0xc0, 0x00, 0x00},{0x80, 0x00, 0x00}};

    int32_t val;

    for (int index = 0; index < numOfValues; index++)
    {
        val = ((buf[index][0] << 24) | (buf[index][1] << 16) | (buf[index][2] << 8)) >> 8;

        std::cout << std::dec << val << std::endl;
        std::cout << std::hex << val << "\n" << std::endl;
    }
}