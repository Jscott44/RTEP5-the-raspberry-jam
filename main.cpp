/* Use the newer ALSA API */
#define ALSA_PCM_NEW_HW_PARAMS_API

#include <cstdint>
#include <iostream>
#include "AlsaBufferConverter.h"
#include <alsa/asoundlib.h>

int main()
{
   int size;
   snd_pcm_t *handle;
   snd_pcm_hw_params_t *params;
   unsigned int val;
   int dir;
   snd_pcm_uframes_t frames;
   char *buffer;

    
    /* To hold error code that is retuened */
    int err; 
    
    /* Device Handle */
    snd_pcm_t *pcm_handle
    
    /* Device Name */
    const char *device_name = "default";

    /* Open the device */
    err = snd_pcm_open (&pcm_handle, device_name, SND_PCM_STREAM_CAPTURE, 0);
    if (rc < 0) {
    fprintf(stderr,
            "unable to open pcm device: %s\n",
            snd_strerror(rc));
    exit(1);
  }
    
  /* Allocate a hardware parameters object. */
  snd_pcm_hw_params_alloca(&params);

  /* Fill it in with default values. */
  snd_pcm_hw_params_any(handle, params);

  /* Set the desired hardware parameters. */

  /* Interleaved mode */
  snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

  /* Signed 24-bit big-endian format (I2S) */
  snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S24_BE);

  /* Two channels (stereo) */
  snd_pcm_hw_params_set_channels(handle, params, 2);

  /* 44100 bits/second sampling rate (CD quality) */
  val = 44100;
  snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);

  /* Set period size to 32 frames. */
  frames = 32;
  snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

    
    
}
