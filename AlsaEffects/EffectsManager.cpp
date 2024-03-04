#include "include/EffectsManager.h"

EffectsManager::EffectsManager()
{
	// Reserve some memory to make it more effecient 
	m_activeEffects.reserve(10);
}

EffectsManager::~EffectsManager()
{

}

EffectBase* EffectsManager::addEffect(EffectIndx desired_effect) //Ptr return will be used to give GUI the pointer it should use when accessing effects
{
	EffectBase* retPtr = nullptr;

	switch (desired_effect)
	{
	case DistortionIndx:
		// Add distortion effect pointer
		retPtr = new Distortion;
		m_activeEffects.push_back(retPtr);
		break;
	case ReverbIndx:
		// Add reverb effect
		retPtr = new Reverb;
		m_activeEffects.push_back(retPtr);
		break;
	default:
		break;
	}

	return retPtr;
}

void EffectsManager::removeEffect(EffectBase* effect)
{
	for (auto it = m_activeEffects.begin(); it != m_activeEffects.end(); ++it)
	{
		if (effect == *it)
		{
			delete* it; *it = nullptr;
			m_activeEffects.erase(it);
			break;
		}
	}
}

ChannelSamples EffectsManager::applyEffect(ChannelSamples initial_data)
{
	ChannelSamples finalData(initial_data.getFramesCount());

	for (auto it = m_activeEffects.begin(); it != m_activeEffects.end(); ++it)
	{
		for (uint16_t sampleIndx = 0; sampleIndx < initial_data.getFramesCount(); ++sampleIndx)
		{
			finalData.appendLeft((*it)->applyEffect(initial_data.getLeftElement(sampleIndx)));
			finalData.appendRight((*it)->applyEffect(initial_data.getRightElement(sampleIndx)));
		}
	}

	return finalData;
}