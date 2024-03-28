#include "include/PcmAudioBase.h"

/// @brief Object handles basics of ALSA setup.
PcmAudioBase::PcmAudioBase(snd_pcm_format_t format, snd_pcm_uframes_t frame_count, unsigned int sample_rate)
	: m_handle(),
	  m_settings(new PcmAudioSettings)
{
	initBaseSettings(format, frame_count, sample_rate);
}

/// @brief Safely closes ALSA and frees members.
PcmAudioBase::~PcmAudioBase()
{
	printf("draining\n");
	// Drain and close ALSA buffer
	snd_pcm_drain(m_handle);
	printf("closing\n");
	snd_pcm_close(m_handle);
	printf("done\n");


	// Free settings object
	if (m_settings != nullptr)
	{
		delete m_settings;
		m_settings = nullptr;
	}
}

/// @brief Initialises common ALSA settings used.
void PcmAudioBase::initBaseSettings(snd_pcm_format_t format, snd_pcm_uframes_t frame_count, unsigned int sample_rate)
{
	// Base settings that are never changed.
	m_settings->access = SND_PCM_ACCESS_RW_INTERLEAVED; // Right Left Interleaved
	m_settings->nchannels = 2; // 2 channels

	// Update parameters from arguments
	m_settings->format = format;
	m_settings->frames = frame_count;
	m_settings->rate = sample_rate; //Change?
	int bytesPerSample = 0;
	switch (format)
	{
	case SND_PCM_FORMAT_S16_LE:
		bytesPerSample = 2;
		break;
	case SND_PCM_FORMAT_S16_BE:
		bytesPerSample = 2;
		break;
	case SND_PCM_FORMAT_S24_LE:
		bytesPerSample = 3;
		break;
	case SND_PCM_FORMAT_S24_BE:
		bytesPerSample = 3;
		break;
	default:
		fprintf(stderr, "Invalid Data Format. Throwing...");
		throw;
		break;
	}
	m_settings->buffer_size = m_settings->frames * m_settings->nchannels * bytesPerSample;
}

/// @brief Opens PCM handle using common settings.
/// @param direction Direction of PCM device (capture or playback)
void PcmAudioBase::openPcmDevice(const char* device_name, snd_pcm_stream_t direction)
{
	// Inspired by:
	//	   https://www.linuxjournal.com/article/6735

	snd_pcm_hw_params_t* params;
	int rc;
	int dir;

	/* Open PCM device for playback. */
	rc = snd_pcm_open(&m_handle, device_name, direction, 0);
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
	snd_pcm_hw_params_set_rate_near(m_handle, params, &m_settings->rate, &dir);

	/* Set period size to 32 frames. */
	snd_pcm_hw_params_set_period_size_near(m_handle, params, &m_settings->frames, &dir);

	/* Write the parameters to the driver */
	rc = snd_pcm_hw_params(m_handle, params);
	if (rc < 0) 
	{
		fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
		exit(1);
	}
}

/// @brief Get settings -> buffer size
/// @return Buffer size.
int PcmAudioBase::getBufferSize()
{
	return m_settings->buffer_size;
}

/// @brief Get settings -> frames
/// @return Number of frames
snd_pcm_uframes_t PcmAudioBase::getFrames()
{
	return m_settings->frames;
}

/// @brief Get ptr to ALSA PCM handle object.
/// @return Ptr to PCM handle.
snd_pcm_t* PcmAudioBase::getHandlePtr()
{
	return m_handle;
}
