#include <alsa/asoundlib.h>
#include <iostream>
#include "src/include/EffectsManager.h"
#include "src/include/PcmAudioCapture.h"
#include "src/include/PcmAudioPlayback.h"
#include "src/include/EffectBase.h"

int main()
{
    //////////// Program Configuration START ////////////

    // Declare audio device names
    const char* captureDevice = "hw:1,1";
    const char* playbackDevice = "default";

    // Optimum Value = 9600;
    snd_pcm_uframes_t framesPerBuffer = 9600;

    // Options: SND_PCM_FORMAT_S16_LE, SND_PCM_FORMAT_S16_BE,  SND_PCM_FORMAT_S24_LE, SND_PCM_FORMAT_S24_BE
    snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE; 

    // Anything works
    unsigned int sampleRate = 96000;

    //////////// Program Configuration END ////////////

    // DO NOT EDIT ANYHTING PAST THIS!!!

    eEndianness endian;
    uint8_t bytesPerSample;
    switch (format)
    {
    case SND_PCM_FORMAT_S16_LE:
        endian = eLITTLE;
        bytesPerSample = 2;
        break;
    case SND_PCM_FORMAT_S16_BE:
        endian = eBIG;
        bytesPerSample = 2;
        break;
    case SND_PCM_FORMAT_S24_LE:
        endian = eLITTLE;
        bytesPerSample = 3;
        break;
    case SND_PCM_FORMAT_S24_BE:
        endian = eBIG;
        bytesPerSample = 3;
        break;
    default:
        fprintf(stderr, "Invalid Format. Ending Program.");
        return 0;
        break;
    }

    EffectsManager* em = new EffectsManager(endian, bytesPerSample, framesPerBuffer);

    PcmAudioPlayback* play = new PcmAudioPlayback(playbackDevice, format, framesPerBuffer, sampleRate);

    PcmAudioCapture* cap = new PcmAudioCapture(captureDevice, format, framesPerBuffer, sampleRate);

    cap->registerCallback(em);
    em->registerCallback(play);

    cap->start();

    getchar();

    printf("\ndeleting cap\n");
    delete cap;
    printf("\ndeleting em\n");
    delete em;
    printf("\ndeleting play\n");
    delete play;
    return 0;
}
