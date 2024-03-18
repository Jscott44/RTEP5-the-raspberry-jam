#include "include/EffectsManager.h"

EffectsManager::EffectsManager()
	:	m_newBuffer(false)
{
	// Reserve some memory to make it more effecient 
	m_activeEffects.reserve(10);

	// Allocate callback buffer on heap
	uint16_t callbackBufferSize = m_bufConverter.getFramesPerBuffer() * m_bufConverter.getSamplesPerFrame() * m_bufConverter.getBytesPerSample();
	m_callbackBuffer = new uint8_t[callbackBufferSize];

	// Initialise thread. Won't start until it receives first signal from callback
	m_effectThread = new std::thread(&EffectsManager::effectLoop, this);

}

EffectsManager::~EffectsManager()
{
	// Stop thread
	m_running = false;
	//m_threadInterface.unblockSignal();

	// Wait for thread to safely terminate
	m_effectThread->join();

	// Delete thread
	delete m_effectThread;
	m_effectThread = nullptr;

	// Delete buffer
	delete m_callbackBuffer;
	m_callbackBuffer = nullptr;
}

void EffectsManager::registerCallback(EffectListener* callback_ptr)
{
	m_callbackPtr = callback_ptr;
}

void EffectsManager::hasBuffer(uint8_t* buffer)
{
	// Store pointer to buffer
	m_listenerBuffer = buffer;

	// Unblock effect loop to process data that has been transfered
	m_newBuffer = true;
	//m_threadInterface.unblockSignal();
}


void EffectsManager::effectLoop()
{
	while (m_running) // Turn false to stop
	{
		//m_threadInterface.waitForSignal(); // Blocking
		
		if (m_newBuffer)
		{
			// Convert buffer into left and right channel ints
			ChannelSamples incomingSamples = m_bufConverter.getSamples(m_listenerBuffer);

			if (!m_alteringEffects) // Will be true if the main thread's GUI is adjusting the values
			{
				// Apply effects
				ChannelSamples outgoingSamples = applyEffect(incomingSamples);

				// Convert new struct back into buffer and store at m_callbackBuffer
				m_bufConverter.getBuffer(m_callbackBuffer, outgoingSamples);
			}
			else // In case GUI is adjusting the effects
			{
				// Convert struct back into buffer and store at m_callbackBuffer
				m_bufConverter.getBuffer(m_callbackBuffer, incomingSamples);
			}

			// Callback
			m_callbackPtr->hasAlteredBuffer(m_callbackBuffer); // Unblock m_listenerPtr
		}
	}

}


EffectBase* EffectsManager::addEffect(EffectIndx desired_effect) //Ptr return will be used to give GUI the pointer it should use when accessing effects
{
	// Tell object that it is not allowed to apply effects
	m_alteringEffects = true;

	EffectBase* retPtr = nullptr;

	// Create desired effect object
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

	// Tell object that is is allowed to apply effects
	m_alteringEffects = false;

	// Return pointer to new object to be used by GUI when accessing effect
	return retPtr;
}

void EffectsManager::removeEffect(EffectBase* effect)
{
	// Tell object that it is not allowed to apply effects
	m_alteringEffects = true;

	// Loop through all stored effects
	for (auto it = m_activeEffects.begin(); it != m_activeEffects.end(); ++it)
	{
		if (effect == *it) // If the effect given in the method argument == a stored method, delete it
		{
			delete* it;
			*it = nullptr;
			m_activeEffects.erase(it);
			break;
		}
	}

	// Tell object that it is allowed to apply effects
	m_alteringEffects = false;
}

ChannelSamples EffectsManager::applyEffect(ChannelSamples initial_data)
{
	// Create struct to store altered data
	ChannelSamples finalData(initial_data.getFramesCount());

	// For each effect stored
	for (auto it = m_activeEffects.begin(); it != m_activeEffects.end(); ++it)
	{
		// For each frame
		for (uint16_t sampleIndx = 0; sampleIndx < initial_data.getFramesCount(); ++sampleIndx)
		{
			// Apply effect to both samples within frame
			finalData.appendLeft((*it)->applyEffect(initial_data.getLeftElement(sampleIndx)));
			finalData.appendRight((*it)->applyEffect(initial_data.getRightElement(sampleIndx)));
		}
	}

	return finalData;
}


void EffectsManager::alterEffect(EffectBase* effect, ParamIndx parameter, int32_t new_val)
{
	return; // Placeholder
}
