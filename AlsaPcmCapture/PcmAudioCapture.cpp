#include "include/PcmAudioCapture.h"

PcmAudioCapture::PcmAudioCapture()
	: PcmAudioBase()
{
}

PcmAudioCapture::~PcmAudioCapture()
{
}

void PcmAudioCapture::initPcmStream()
{
	m_settings->direction = SND_PCM_STREAM_CAPTURE;
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
		rc = snd_pcm_readi(getPcmHandle(), getBuffer(), getFrames());
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

		m_callbackPtr->hasBuffer(getBuffer());
	}

	snd_pcm_drain(getPcmHandle());
}