#define BOOST_TEST_MODULE AlsaBufferConverterTests
#include <boost/test/unit_test.hpp>
#include "AlsaBufferConverter.h"


BOOST_AUTO_TEST_CASE(PassTest)
{
    uint8_t originalData[] = { 0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 ,
                      0x7F, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00 };


	AlsaBufferConverter test;
    ChannelSamples exampleSamples = test.getSamples(buf);
    std::unique_ptr<uint8_t> returnedData = test.getBuffer(egSamples);
	
    for (int index = 0; index < (test.getBytesPerSample() * test.getSamplesPerFrame * test.getFramesPerBuffer()); ++index)
    {
        BOOST_CHECK_EQUAL(originalData[index],returnedData.get()[index]);
    }
}
