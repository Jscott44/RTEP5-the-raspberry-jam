#ifndef PCMAUDIOCAPTURE_H
#define PCMAUDIOCAPTURE_H

#include "PcmAudioBase.h"
#include <thread>

class PcmAudioCapture : public PcmAudioBase
{
public:
	PcmAudioCapture();
	~PcmAudioCapture();

	void registerCallback(AlsaListener* callback_ptr);
private:
	void initPcmStream() override;
	void createBuffer() override;

	AlsaListener* m_callbackPtr;
};


// PLACEHOLDER: DELETE LATER
class AlsaListener
{
public:
	virtual void hasBuffer(uint8_t* buffer) = 0;
};

#endif // !PCMAUDIOCAPTURE_H
