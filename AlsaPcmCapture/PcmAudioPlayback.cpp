#include "include/PcmAudioPlayback.h"

PcmAudioPlayback::PcmAudioPlayback()
	: PcmAudioBase()
{
}

PcmAudioPlayback::~PcmAudioPlayback()
{
}

snd_pcm_stream_t PcmAudioPlayback::getStreamDirection()
{
	return SND_PCM_STREAM_PLAYBACK;
}

void PcmAudioPlayback::pcmLoop()
{
	int rc;

	while (m_running)
	{
		// Blocking method here

		rc = snd_pcm_writei(m_handle, m_buffer, getFrames());
		if (rc == -EPIPE) {
			/* EPIPE means underrun */
			fprintf(stderr, "underrun occurred\n");
			snd_pcm_prepare(m_handle);
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

	snd_pcm_drain(m_handle);
}

void PcmAudioPlayback::hasAlteredBuffer(uint8_t* buffer)
{
	m_buffer = buffer;

	// Unblock pcmLoop
}