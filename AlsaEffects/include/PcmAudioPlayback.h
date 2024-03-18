#ifndef PCMAUDIOPLAYBACK_H
#define PCMAUDIOPLAYBACK_H

#include "EffectListener.h"
#include "PcmAudioBase.h"
#include <cstdint>

class PcmAudioPlayback : public PcmAudioBase , public EffectListener
{
public:
	PcmAudioPlayback();
	~PcmAudioPlayback();

private:
	// Effect Listener
	void hasAlteredBuffer(uint8_t* buffer) override;
};



#endif // !PCMAUDIOPLAYBACK_H
