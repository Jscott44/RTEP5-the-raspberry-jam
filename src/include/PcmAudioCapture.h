#ifndef PCMAUDIOCAPTURE_H
#define PCMAUDIOCAPTURE_H

#include "AlsaListener.h"
#include "PcmAudioBase.h"
#include "DataFormat.h"
#include <cstdint>
#include <thread>


class PcmAudioCapture : public PcmAudioBase
{
public:
	PcmAudioCapture(const char* device_name, snd_pcm_format_t format, snd_pcm_uframes_t frame_count, unsigned int sample_rate);
	~PcmAudioCapture();

	void registerCallback(AlsaListener* callback_ptr);

	/*starts background capture/playback of data, callback when buffer is full/ready for new data */
	void start();
	void stop();
private:
	void pcmLoop();

	bool m_running;
	std::thread* m_thread;

	uint8_t* m_buffer; // Buffer to store samples

	// Callbacks
	AlsaListener* m_callbackPtr;
};




#endif // !PCMAUDIOCAPTURE_H
