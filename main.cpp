#include <alsa/asoundlib.h>
#include <iostream>
#include "AlsaEffects/include/AlsaBufferConverter.h"
#include "AlsaEffects/include/EffectsManager.h"
#include "AlsaEffects/include/PcmAudioCapture.h"
#include "AlsaEffects/include/PcmAudioPlayback.h"
#include <memory>
#include "AlsaEffects/include/EffectBase.h"

int main()
{
    EffectsManager* em = new EffectsManager;

    PcmAudioPlayback* play = new PcmAudioPlayback;

    PcmAudioCapture* cap = new PcmAudioCapture;

    cap->registerCallback(em);
    em->registerCallback(play);

    cap->start();

    getchar();

    printf("1");

    delete em;
        printf("1");

    delete play;
        printf("1");

    delete cap;
        printf("1");


    return 0;
}
