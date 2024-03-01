#include <alsa/asoundlib.h>

#ifndef ALSAPCMCAPTURE_H
#define ALSAPCMCAPTURE_H

struct PcmAudioSettings {


/* create device handle object */
snd_pcm_t *handle; 

/* device name (default pcm device) */
const char *device_name;




/* create params object */
snd_pcm_hw_params_t *params;

/* number of audio frames stored in buffer (period size))*/
snd_pcm_uframes_t frames;

/* audio format mode */
snd_pcm_format_t format;

/* sample rate */
unsigned int rate;

/* number of channels */
unsigned int nchannels;


/* buffer that digital audio will  be written to after capture */
char *buffer;

/* buffer size should be enough to contain one period */
int buffer_size;


};

class PcmCapture
{
	public:
		void startI2S(){}
		
		/*callback for when buffer that is wriiten to after read is full */
		virtual void bufferReady() = 0;
			
	
	

	private:
	

	
	
	


};

#endif
