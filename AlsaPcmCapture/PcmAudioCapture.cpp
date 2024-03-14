#include "include/PcmAudioCapture.h"

PcmAudioCapture::PcmAudioCapture()
	: PcmAudioBase(),
	  m_running(false),
	  m_thread(nullptr),
	  m_buffer(new uint8_t[getBufferSize()])
{
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

snd_pcm_stream_t PcmAudioCapture::getStreamDirection()
{
	return SND_PCM_STREAM_CAPTURE;
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
	if (m_running = false && m_pcmThread == nullptr)
	{
		m_running = true;
		m_pcmThread = new std::thread(PcmAudioBase::pcmLoop, this);
	}
}

void PcmAudioCapture::stop()
{
	if (m_running = true)
	{
		m_running = false;
		m_pcmThread->join();

		delete m_pcmThread;
		m_pcmThread == nullptr;
	}
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
			fprint(stdout, "i2s read successful");
		}

		m_callbackPtr->hasBuffer(m_buffer);
	}
}