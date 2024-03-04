#ifndef EFFECTSMANAGER_H
#define EFFECTSMANAGER_H
#include <cstdint>
#include <vector>
#include "EffectBase.h"
#include "AlsaBufferConverter.h"

class EffectsManager
{
public:
	EffectsManager(); // Placeholder
	~EffectsManager(); // Placeholder

	EffectBase* addEffect(EffectIndx desired_effect);
	void removeEffect(EffectBase* effect);

	ChannelSamples applyEffect(ChannelSamples initial_data);

private:
	std::vector<EffectBase*> m_activeEffects;
};

#endif