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
			/* EPIPE means underrun */
			fprintf(stderr, "underrun occurred\n");
			snd_pcm_prepare(getHandlePtr());
		}
		else if (rc < 0)
		{
			fprintf(stderr, "error from readi: %s\n", snd_strerror(rc));
		}
		else if (rc != (int)getFrames())
		{
			fprintf(stderr, "short read, read %d frames\n", rc);
		}
		else
		{
			fprintf(stdout, "i2s read successful\n");
		}

		// Pass buffer to callback interface
		m_callbackPtr->hasBuffer(m_buffer);
	}
}
