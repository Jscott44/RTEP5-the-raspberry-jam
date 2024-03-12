#ifndef PCMAUDIOPLAYBACK_H
#define PCMAUDIOPLAYBACK_H

#include "PcmAudioBase.h"

class PcmAudioPlayback : public PcmAudioBase , public EffectListener
{
public:
	PcmAudioPlayback();
	~PcmAudioPlayback();

private:
	void initPcmStream() override;
	void createBuffer() override;

	void hasAlteredBuffer(uint8_t* buffer) override;
};

// PLACEHOLDER: DELETE LATER
class EffectListener
{
public:
	virtual void hasAlteredBuffer(uint8_t* buffer) = 0;
};

#endif // !PCMAUDIOPLAYBACK_H
