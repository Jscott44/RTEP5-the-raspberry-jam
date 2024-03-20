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

    PcmAudioPlayback* play = new PcmAudioPlayback("default");

    PcmAudioCapture* cap = new PcmAudioCapture("default");

    cap->registerCallback(em);
    em->registerCallback(play);

    cap->start();
    //cap->stop();


    getchar();

    printf("\ndeleting cap\n");
    delete cap;
    printf("\ndeleting em\n");
    delete em;
    printf("\ndeleting play\n");
    delete play;
    return 0;
}
