#include "include/PcmAudioCapture.h"

PcmAudioCapture::PcmAudioCapture()
	: PcmAudioBase()
{
	if (m_buffer == nullptr)
	{
		m_buffer = new uint8_t[getBufferSize()];
	}
}

PcmAudioCapture::~PcmAudioCapture()
{
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

void PcmAudioCapture::pcmLoop()
{
	int rc;

	while (m_running) 
	{
		rc = snd_pcm_readi(m_handle, m_buffer, getFrames());
		if (rc < 0) {
			fprintf(stderr, "error from readi: %s\n", snd_strerror(rc));
		}
		else if (rc != (int)getFrames()) {
			fprintf(stderr, "short read, read %d frames\n", rc);
		}

		//if (rc == -EPIPE) {
		//	/* EPIPE means underrun */
		//	fprintf(stderr, "underrun occurred\n");
		//	snd_pcm_prepare(handle);
		//}

		m_callbackPtr->hasBuffer(m_buffer);
	}

	snd_pcm_drain(getPcmHandle());
}