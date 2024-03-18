#include "include/PcmAudioBase.h"

PcmAudioBase::PcmAudioBase()
	: m_handle(),
	  m_settings(new PcmAudioSettings)
{
	initBaseSettings();
}

PcmAudioBase::~PcmAudioBase()
{
	snd_pcm_drain(m_handle);
	snd_pcm_close(m_handle);

	if (m_settings != nullptr)
	{
		delete m_settings;
		m_settings = nullptr;
	}
}

void PcmAudioBase::initBaseSettings()
{
	m_settings->device_name = "default";
	m_settings->access = SND_PCM_ACCESS_RW_INTERLEAVED;
	m_settings->format = SND_PCM_FORMAT_S24_BE;
	m_settings->rate = 44100;
	m_settings->nchannels = 2;
	m_settings->frames = 44;
	m_settings->buffer_size = m_settings->frames * 3 * 2; /*3 bytes per channel, 2 channels */
}

void PcmAudioBase::openPcmDevice(snd_pcm_stream_t direction)
{
	// Inspired by:
	//	   https://www.linuxjournal.com/article/6735

	snd_pcm_hw_params_t* params;
	int rc;
	int dir;

	/* Open PCM device for playback. */
	rc = snd_pcm_open(&m_handle, "default", direction, 0);
	if (rc < 0) 
	{
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		exit(1);
	}

	/* Allocate a hardware parameters object. */
	snd_pcm_hw_params_alloca(&params);

	/* Fill it in with default values. */
	snd_pcm_hw_params_any(m_handle, params);

	/* Set the desired hardware parameters. */

	/* Interleaved mode */
	snd_pcm_hw_params_set_access(m_handle, params, m_settings->access);

	/* Signed 16-bit little-endian format */
	snd_pcm_hw_params_set_format(m_handle, params, m_settings->format);

	/* Two channels (stereo) */
	snd_pcm_hw_params_set_channels(m_handle, params, m_settings->nchannels);

	/* 44100 bits/second sampling rate (CD quality) */
	unsigned int rate = m_settings->rate;
	//snd_pcm_hw_params_set_rate_near(m_handle, params, &rate, &dir);
	snd_pcm_hw_params_set_rate_near(m_handle, params, &m_settings->rate, &dir);


	/* Set period size to 32 frames. */
	snd_pcm_uframes_t frames = m_settings->frames;
	//snd_pcm_hw_params_set_period_size_near(m_handle, params, &frames, &dir);
	snd_pcm_hw_params_set_period_size_near(m_handle, params, &m_settings->frames, &dir);


	/* Write the parameters to the driver */
	rc = snd_pcm_hw_params(m_handle, params);
	if (rc < 0) 
	{
		fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
		exit(1);
	}

	/* Free params*/
	//snd_pcm_hw_params_free(params);
}

int PcmAudioBase::getBufferSize()
{
	return m_settings->buffer_size;
}

snd_pcm_uframes_t PcmAudioBase::getFrames()
{
	return m_settings->frames;
}

snd_pcm_t* PcmAudioBase::getHandlePtr()
{
	return m_handle;
}

