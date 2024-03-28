#include <alsa/asoundlib.h>
#include <iostream>
#include "src/include/EffectsManager.h"
#include "src/include/PcmAudioCapture.h"
#include "src/include/PcmAudioPlayback.h"
#include "src/include/EffectBase.h"
#include "src/include/GuiSimulator.h"

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

    GuiSimulator* gui = new GuiSimulator();

    EffectsManager* em = new EffectsManager(endian, bytesPerSample, framesPerBuffer);

    PcmAudioPlayback* play = new PcmAudioPlayback(playbackDevice, format, framesPerBuffer, sampleRate);

    PcmAudioCapture* cap = new PcmAudioCapture(captureDevice, format, framesPerBuffer, sampleRate);

    gui->registerCallback(em);
    cap->registerCallback(em);
    em->registerCallback(play);

    cap->start();
    getchar();

    // Add distortion
    EffectBase* effect = gui->addEffect(DistortionIndx);
    getchar();

    // Increase gain 1->50
    gui->alterEffect(effect,eGain,50);
    getchar();

    // Remove distortion
    gui->removeEffect(effect);
    getchar();

    // Add reverb
    effect = gui->addEffect(ReverbIndx);
    getchar();

    // Change Delay 100 -> 400
    gui->alterEffect(effect, eDelayMs, 100);
    getchar();

    // Change Decay 0.2 -> 0.8
    gui->alterEffect(effect, eDecay, 0.2);
    getchar();

    // Remove distortion
    gui->removeEffect(effect);
    getchar();

    printf("\ndeleting cap\n");
    delete cap;
    printf("\ndeleting em\n");
    delete em;
    printf("\ndeleting play\n");
    delete play;
    printf("\ndeleting gui\n");
    delete gui;
    return 0;
}
