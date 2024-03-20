#include "include/PcmAudioCapture.h"

/// @brief Object can be used to capture I2S Int24s being received at the PCM pins on the RPI.
PcmAudioCapture::PcmAudioCapture()
	: PcmAudioBase(),
	  m_running(false),
	  m_thread(nullptr),
	  m_buffer(new uint8_t[getBufferSize()])
{
	// Open device and specify that this object captures
	openPcmDevice(SND_PCM_STREAM_CAPTURE);
}

/// @brief Safely stops capture and frees allocated memory.
PcmAudioCapture::~PcmAudioCapture()
{
	stop();

	if (m_buffer != nullptr)
	{
		delete m_buffer;
		m_buffer == nullptr;
	}

	printf("Capture destroyed\n");
}

/// @brief Registers callback interface object that will receive callbacks from this object.
/// @param callback_ptr Ptr to a callback interface object.
void PcmAudioCapture::registerCallback(AlsaListener* callback_ptr)
{
	m_callbackPtr = callback_ptr; // Store ptr
}

/// @brief Starts PCM capture. Runs until stop() is called or object is destroyed.Fails if callback interface has not been registered (see registerCallback()).
void PcmAudioCapture::start()
{
	// Should not start if callback interface has not been registered.
	if (m_callbackPtr == nullptr)
	{
		fprintf(stderr, "Callback not registered. Exiting...\n");
		return;
	}

	// Start thread used for capture
	if (m_running == false && m_thread == nullptr)
	{
		m_running = true;
		m_thread = new std::thread(&PcmAudioCapture::pcmLoop, this);
	}
}

/// @brief Stops PCM capture.
void PcmAudioCapture::stop()
{
	printf("entering stop\n");
	if (m_running == true && m_thread != nullptr)
	{
		m_running = false;
		printf("joining t\n");
		m_thread->join();
		printf("t terminated\n");

		delete m_thread;
		m_thread == nullptr;
	}
	printf("exiting stop\n");
}

/// @brief Continually reads PCM signals before using callback.
void PcmAudioCapture::pcmLoop()
{
	// Inspired by:
	//	   https://www.linuxjournal.com/article/6735

	int rc;

	while (m_running) 
	{
		rc = snd_pcm_readi(getHandlePtr(), m_buffer, getFrames()); // Blocking
		if (rc == -EPIPE)
		{
			/* EPIPE means overrun */
			fprintf(stderr, "overrun occurred\n");
			snd_pcm_prepare(getHandlePtr());
			continue;
		}
		else if (rc < 0)
		{
			fprintf(stderr, "error from readi: %s\n", snd_strerror(rc));
			continue;
		}
		else if (rc != (int)getFrames())
		{
			fprintf(stderr, "short read, read %d frames\n", rc);
			continue;
		}
		else
		{
			fprintf(stdout, "i2s read successful\n");
		}

		// Pass buffer to callback interface
		m_callbackPtr->hasBuffer(m_buffer);
	}
}

// /// @brief Continually reads PCM signals before using callback.
// void PcmAudioCapture::pcmLoop()
// {
// 	// Inspired by:
// 	//	   https://www.linuxjournal.com/article/6735

// 	snd_pcm_hw_params_t* params;
// 	int rc;
// 	int dir;

// 	int size;
// 	unsigned int val;
// 	snd_pcm_uframes_t frames;

// 	/* Open PCM device for playback. */
// 	rc = snd_pcm_open(&m_handle, "default", SND_PCM_STREAM_CAPTURE, 0);
// 	if (rc < 0) 
// 	{
// 		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
// 		exit(1);
// 	}

// 	/* Allocate a hardware parameters object. */
// 	snd_pcm_hw_params_alloca(&params);

// 	/* Fill it in with default values. */
// 	snd_pcm_hw_params_any(m_handle, params);

// 	/* Set the desired hardware parameters. */

// 	/* Interleaved mode */
// 	snd_pcm_hw_params_set_access(m_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

// 	/* Signed 16-bit little-endian format */
// 	snd_pcm_hw_params_set_format(m_handle, params, SND_PCM_FORMAT_S24_BE);

// 	/* Two channels (stereo) */
// 	snd_pcm_hw_params_set_channels(m_handle, params, 2);

// 	/* 44100 bits/second sampling rate (CD quality) */
// 	val = 44100;
// 	snd_pcm_hw_params_set_rate_near(m_handle, params, &val, &dir);

// 	/* Set period size to 32 frames. */
// 	frames = 44;
// 	snd_pcm_hw_params_set_period_size_near(m_handle, params, &frames, &dir);

// 	/* Write the parameters to the driver */
// 	rc = snd_pcm_hw_params(m_handle, params);
// 	if (rc < 0) 
// 	{
// 		fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
// 		exit(1);
// 	}

// 	while (m_running) 
// 	{
// 		rc = snd_pcm_readi(getHandlePtr(), m_buffer, getFrames()); // Blocking
// 		if (rc == -EPIPE)
// 		{
// 			/* EPIPE means underrun */
// 			fprintf(stderr, "underrun occurred\n");
// 			snd_pcm_prepare(getHandlePtr());
// 		}
// 		else if (rc < 0)
// 		{
// 			fprintf(stderr, "error from readi: %s\n", snd_strerror(rc));
// 		}
// 		else if (rc != (int)getFrames())
// 		{
// 			fprintf(stderr, "short read, read %d frames\n", rc);
// 		}
// 		else
// 		{
// 			fprintf(stdout, "i2s read successful\n");
// 		}

// 		// Pass buffer to callback interface
// 		m_callbackPtr->hasBuffer(m_buffer);
// 	}

// 	printf("draining\n");
// 	// Drain and close ALSA buffer
// 	snd_pcm_drain(m_handle);
// 	printf("closing\n");
// 	snd_pcm_close(m_handle);
// 	printf("done\n");
// }
