#include <alsa/asoundlib.h>
#include <iostream>
#include "AlsaEffects/include/EffectsManager.h"
#include "AlsaEffects/include/PcmAudioCapture.h"
#include "AlsaEffects/include/PcmAudioPlayback.h"
#include "AlsaEffects/include/EffectBase.h"

int main()
{
    //////////// Program Configuration START ////////////

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

    PcmAudioPlayback* play = new PcmAudioPlayback("default", format, framesPerBuffer, sampleRate);

    PcmAudioCapture* cap = new PcmAudioCapture("hw:1,1", format, framesPerBuffer, sampleRate);

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
