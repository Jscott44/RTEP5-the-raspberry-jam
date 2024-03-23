#ifndef PCMAUDIOPLAYBACK_H
#define PCMAUDIOPLAYBACK_H

#include "EffectListener.h"
#include "PcmAudioBase.h"
#include <cstdint>

class PcmAudioPlayback : public PcmAudioBase , public EffectListener
{
public:
	PcmAudioPlayback(const char* device_name, snd_pcm_format_t format, snd_pcm_uframes_t frame_count, unsigned int sample_rate);
	~PcmAudioPlayback();

private:
	// Effect Listener
	void hasAlteredBuffer(uint8_t* buffer) override;
};



#endif // !PCMAUDIOPLAYBACK_H
