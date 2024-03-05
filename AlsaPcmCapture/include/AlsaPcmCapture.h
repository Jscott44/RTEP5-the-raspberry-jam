#include <alsa/asoundlib.h>

#ifndef ALSAAUDIODRIVER_H
#define ALSAAUDIODRIVER_H

struct PcmAudioSettings 
{

/* device name (default pcm device) */
const char *device_name;

/* number of audio frames stored in buffer (period size))*/
snd_pcm_uframes_t frames;

/* sample rate */
unsigned int rate;

/* number of channels */
unsigned int nchannels;

/* buffer size should be enough to contain one period */
int buffer_size;

/* digital audio format */
snd_pcm_format_t format;

};

class PcmAudioDriver
{
	public:
		
		PcmAudioDriver()
		{
			
			m_settings = new PcmAudioSettings;
			
			m_settings->device_name = "default";
			
			/* device handle object */
			snd_pcm_t *handle; 
			
			m_settings->frames = 44;
			
			m_settings->rate = 44100;
			
			m_settings->nchannels = 2;
			
			m_settings->buffer_size = m_settings->frames*3*2; /*3 bytes per channel, 2 channels */ 
			
			m_settings->format = SND_PCM_FORMAT_S24_BE;
			
		}
		
		virtual void openPcmDevice ();
		
		~PcmAudioDriver() //destructor
		{
			delete m_settings;
		}
		
		/*handles error codes*/
		int m_err;
		
		/*starts background capture/playback of data, callback when buffer is full/ready for new data */
		void startI2S(){}
		
		/*callback for when buffer that is written to/reda from after read is full/ready */
		virtual void bufferReady(char* buffer) = 0;
			
	

	private:
		/* settings object */
		PcmAudioSettings* m_settings;
};

/*driver base class with capture and playback being children of it in order to share basic settings*/

class PcmAudioCapture: public PcmAudioDriver
{
	
	public:
		
	private:
	
		char* m_captureBuffer;
		snd_pcm_hw_params_t *params;
	
	
};

class PcmAudioPlayback: public PcmAudioDriver
{
	
	
};

#endif
