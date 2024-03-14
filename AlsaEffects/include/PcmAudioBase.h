#ifndef PCMAUDIOBASE_H
#define PCMAUDIOBASE_H

#include <cstdint>
#include <alsa/asoundlib.h>

class PcmAudioBase
{
public:

	PcmAudioBase();
	~PcmAudioBase(); //destructor
protected:
	// Methods used by children classes
	int getBufferSize();
	snd_pcm_uframes_t getFrames();
	snd_pcm_t* getHandlePtr();
private:
	virtual snd_pcm_stream_t getStreamDirection() = 0; // Initialises Pcm Stream Direction. Must be initialised for each child to ensure the stream is desired

	void initBaseSettings();
	void openPcmDevice();

	snd_pcm_t* m_handle;

	/* settings object */
	PcmAudioSettings* m_settings;
};


struct PcmAudioSettings
{
	const char* device_name; /* device name (default pcm device) */
	snd_pcm_access_t access; /* data access type */
	snd_pcm_format_t format;/* digital audio format */
	snd_pcm_uframes_t frames; /* number of audio frames stored in buffer (period size))*/
	unsigned int rate; /* sample rate */
	unsigned int nchannels; /* number of channels */
	int buffer_size; /* buffer size should be enough to contain one period */
};

#endif // !PCMAUDIOBASE_H
