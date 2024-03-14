#ifndef PCMAUDIOPLAYBACK_H
#define PCMAUDIOPLAYBACK_H

#include "EffectListener.h"
#include "PcmAudioBase.h"

class PcmAudioPlayback : public PcmAudioBase , public EffectListener
{
public:
	PcmAudioPlayback();
	~PcmAudioPlayback();

private:
	// Pcm Audio Base
	snd_pcm_stream_t getStreamDirection() override;

	// Effect Listener
	void hasAlteredBuffer(uint8_t* buffer) override;
};



#endif // !PCMAUDIOPLAYBACK_H
