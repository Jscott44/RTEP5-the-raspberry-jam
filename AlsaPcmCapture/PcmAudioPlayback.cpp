#include "include/PcmAudioPlayback.h"

PcmAudioPlayback::PcmAudioPlayback()
	: PcmAudioBase()
{
}

PcmAudioPlayback::~PcmAudioPlayback()
{
}

void PcmAudioPlayback::initPcmStream()
{
	m_settings->direction = SND_PCM_STREAM_PLAYBACK;
}

void PcmAudioPlayback::createBuffer()
{
	return; // We use buffer obtained in callback and therefore do not need to create our own
}

void PcmAudioPlayback::pcmLoop()
{
	while (m_running)
	{
		// Blocking method here

		rc = snd_pcm_writei(getPcmHandle(), m_buffer, getFrames());
		if (rc == -EPIPE) {
			/* EPIPE means underrun */
			fprintf(stderr, "underrun occurred\n");
			snd_pcm_prepare(handle);
		}
		else if (rc < 0) {
			fprintf(stderr,
				"error from writei: %s\n",
				snd_strerror(rc));
		}
		else if (rc != (int)getFrames()) {
			fprintf(stderr,
				"short write, write %d frames\n", rc);
		}
	}

	snd_pcm_drain(getPcmHandle());
}

void PcmAudioPlayback::hasAlteredBuffer(uint8_t* buffer)
{
	m_buffer = buffer;

	// Unblock pcmLoop
}