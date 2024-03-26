#include "include/PcmAudioPlayback.h"

/// @brief Object can be used to write I2S signals to the PCM pins of the RPI.
PcmAudioPlayback::PcmAudioPlayback(const char* device_name, snd_pcm_format_t format, snd_pcm_uframes_t frame_count, unsigned int sample_rate)
	: PcmAudioBase(format, frame_count, sample_rate)
{
	// Open device and specify that this object is used for playback
	openPcmDevice(device_name, SND_PCM_STREAM_PLAYBACK);
}


PcmAudioPlayback::~PcmAudioPlayback()
{
}

/// @brief From EffectListener. Writes received buffer to the PCM pins.
/// @param buffer Buffer containing the samples that should be written.
void PcmAudioPlayback::hasAlteredBuffer(uint8_t* buffer)
{
	// Inspired by:
	//	   https://www.linuxjournal.com/article/6735

	int rc = snd_pcm_writei(getHandlePtr(), buffer, getFrames()); //Blocking
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
		//fprintf(stdout, "i2s write successful\n");
	}
}
