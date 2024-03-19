#include "include/PcmAudioCapture.h"

PcmAudioCapture::PcmAudioCapture()
	: PcmAudioBase(),
	  m_running(false),
	  m_thread(nullptr),
	  m_buffer(new uint8_t[getBufferSize()])
{
	openPcmDevice(SND_PCM_STREAM_CAPTURE);
}

PcmAudioCapture::~PcmAudioCapture()
{
	stop();

	if (m_buffer != nullptr)
	{
		delete m_buffer;
		m_buffer == nullptr;
	}
}

void PcmAudioCapture::registerCallback(AlsaListener* callback_ptr)
{
	m_callbackPtr = callback_ptr;
}

void PcmAudioCapture::start()
{
	if (m_callbackPtr == nullptr)
	{
		fprintf(stderr, "Callback not registered");
		return;
	}

	if (m_running == false && m_thread == nullptr)
	{
		m_running = true;
		m_thread = new std::thread(&PcmAudioCapture::pcmLoop, this);
	}
}

void PcmAudioCapture::stop()
{
	printf("entering stop");
	if (m_running == true && m_thread != nullptr)
	{
		m_running = false;
		m_thread->join();

		delete m_thread;
		m_thread == nullptr;
	}
	printf("entering stop");
}

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
			fprintf(stdout, "i2s read successful. %d frames have been read.\n", rc);
		}

		m_callbackPtr->hasBuffer(m_buffer);
	}
}
