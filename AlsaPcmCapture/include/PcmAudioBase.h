#ifndef PCMAUDIOBASE_H
#define PCMAUDIOBASE_H

#include <cstdint>
#include <alsa/asoundlib.h>
#include <thread>

class PcmAudioBase
{
public:

	PcmAudioBase();
	~PcmAudioBase(); //destructor

	/*starts background capture/playback of data, callback when buffer is full/ready for new data */
	void start();
	void stop();
protected:
	int getBufferSize();
	snd_pcm_uframes_t getFrames();

	snd_pcm_t* m_handle;

	// Buffer to store samples
	uint8_t* m_buffer;

	bool m_running;

private:
	virtual void pcmLoop() = 0;
	virtual snd_pcm_stream_t getStreamDirection() = 0; // Initialises Pcm Stream Direction. Must be initialised for each child to ensure the stream is desired

	void initBaseSettings();
	void openPcmDevice();

	/* settings object */
	PcmAudioSettings* m_settings;

	std::thread* m_pcmThread;
};


struct PcmAudioSettings
{
	const char* device_name; /* device name (default pcm device) */
	snd_pcm_access_t access;
	snd_pcm_format_t format;/* digital audio format */
	snd_pcm_uframes_t frames; /* number of audio frames stored in buffer (period size))*/
	unsigned int rate; /* sample rate */
	unsigned int nchannels; /* number of channels */
	int buffer_size; /* buffer size should be enough to contain one period */
};

#endif // !PCMAUDIOBASE_H
