#ifndef PCMAUDIOCAPTURE_H
#define PCMAUDIOCAPTURE_H

#include "AlsaListener.h"
#include "PcmAudioBase.h"
#include <thread>


class PcmAudioCapture : public PcmAudioBase
{
public:
	PcmAudioCapture();
	~PcmAudioCapture();

	void registerCallback(AlsaListener* callback_ptr);

	/*starts background capture/playback of data, callback when buffer is full/ready for new data */
	void start();
	void stop();
private:
	// Pcm Audio Base
	snd_pcm_stream_t getStreamDirection() override;

	void pcmLoop();

	bool m_running;
	std::thread* m_thread;

	uint8_t* m_buffer; // Buffer to store samples

	// Callbacks
	AlsaListener* m_callbackPtr;
};




#endif // !PCMAUDIOCAPTURE_H
