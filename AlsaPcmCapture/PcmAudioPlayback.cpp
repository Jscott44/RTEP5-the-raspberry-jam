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

void PcmAudioPlayback::hasAlteredBuffer(uint8_t* buffer)
{
	// Inspired by:
	//	   https://www.linuxjournal.com/article/6735

	int rc = snd_pcm_writei(getHandlePtr(), buffer, getFrames());
	if (rc == -EPIPE)
	{
		/* EPIPE means underrun */
		fprintf(stderr, "underrun occurred\n");
		snd_pcm_prepare(getHandlePtr());
	}
	else if (rc < 0)
	{
		fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
	}
	else if (rc != (int)getFrames())
	{
		fprintf(stderr, "short write, write %d frames\n", rc);
	}
	else
	{
		fprint(stdout, "i2s write successful");
	}
}