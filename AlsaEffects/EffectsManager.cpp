#include "include/EffectsManager.h"

EffectsManager::EffectsManager()
{
	// Reserve some memory to make it more effecient 
	m_activeEffects.reserve(10);

	// Allocate callback buffer on heap
	uint16_t callbackBufferSize = m_bufConverter.getFramesPerBuffer() * m_bufConverter.getSamplesPerFrame() * m_bufConverter.getBytesPerSample();
	m_callbackBuffer = new uint8_t[callbackBufferSize];

}

EffectsManager::~EffectsManager()
{
	delete m_callbackBuffer;
	m_callbackBuffer = nullptr;
}

void EffectsManager::registerCallback(EffectListener* callback_ptr)
{
	m_callbackPtr = callback_ptr;
}

void EffectsManager::hasBuffer(uint8_t* buffer)
{
	m_listenerBuffer = buffer;

	m_threadInterface.unblockSignal();
}


void EffectsManager::effectLoop()
{
	while (m_running)
	{
		m_threadInterface.waitForSignal(); // Blocking

		if (!m_alteringEffects)
		{
			ChannelSamples incomingSamples = m_bufConverter.getSamples(m_listenerBuffer);

			ChannelSamples outgoingSamples = applyEffect(incomingSamples);

			m_bufConverter.getBuffer(outgoingSamples, m_callbackBuffer);

			m_callbackPtr->hasAlteredBuffer(m_callbackBuffer); // Unblock m_listenerPtr
		}
		else
		{
			m_callbackPtr->hasAlteredBuffer(m_callbackBuffer);
		}
	}

}


EffectBase* EffectsManager::addEffect(EffectIndx desired_effect) //Ptr return will be used to give GUI the pointer it should use when accessing effects
{
	EffectBase* retPtr = nullptr;

	m_alteringEffects = true;

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

	m_alteringEffects = false;

	return retPtr;
}

void EffectsManager::removeEffect(EffectBase* effect)
{
	m_alteringEffects = true;

	for (auto it = m_activeEffects.begin(); it != m_activeEffects.end(); ++it)
	{
		if (effect == *it)
		{
			delete* it;
			*it = nullptr;
			m_activeEffects.erase(it);
			break;
		}
	}

	m_alteringEffects = false;
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