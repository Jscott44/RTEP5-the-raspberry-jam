#include <alsa/asoundlib.h>
#include <iostream>
#include "AlsaEffects/include/AlsaBufferConverter.h"
#include "AlsaEffects/include/EffectsManager.h"
#include "AlsaEffects/include/PcmAudioCapture.h"
#include "AlsaEffects/include/PcmAudioPlayback.h"
#include <memory>

int main()
{
    EffectsManager* em = new EffectsManager;

    PcmAudioPlayback* play = new PcmAudioPlayback;

    PcmAudioCapture* cap = new PcmAudioCapture;

    cap->registerCallback(em);
    em->registerCallback(play);

    cap->start();

    getchar();

    return 0;
}
