#include "include/EffectsManager.h"

EffectsManager::EffectsManager()
	:	GuiListener(),
		AlsaListener(),
		m_newBuffer(false),
		m_running(false)
{
	// Reserve some memory to make it more effecient 
	m_activeEffects.reserve(10);

	m_alteringEffects = false;

	// Allocate callback buffer on heap
	uint16_t callbackBufferSize = m_bufConverter.getFramesPerBuffer() * m_bufConverter.getSamplesPerFrame() * m_bufConverter.getBytesPerSample();
	m_callbackBuffer = new uint8_t[callbackBufferSize];

	// Initialise thread. Won't start until it receives first signal from callback
	m_running = true;
	m_thread = new std::thread(&EffectsManager::effectLoop, this);


}

EffectsManager::~EffectsManager()
{
	// Stop thread
	m_running = false;

	// Wait for thread to safely terminate
	m_thread->join();

	// Delete thread
	delete m_thread;
	m_thread = nullptr;

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

}


void EffectsManager::effectLoop()
{
	printf("Entering effect loop");

	ChannelSamples incomingSamples(44);
	ChannelSamples outgoingSamples(44);


	while (m_running) // Turn false to stop
	{		
		if (m_newBuffer)
		{
			printf("new buffer received \n");

			m_newBuffer = false;

			// Convert buffer into left and right channel ints
			m_bufConverter.getSamples(&incomingSamples, m_listenerBuffer);

			if (!m_alteringEffects) // Will be true if the main thread's GUI is adjusting the values
			{
				// Apply effects
				applyEffect(&outgoingSamples, &incomingSamples);

				// Convert new struct back into buffer and store at m_callbackBuffer
				m_bufConverter.getBuffer(m_callbackBuffer, &outgoingSamples);
			}
			else // In case GUI is adjusting the effects
			{
				// Convert struct back into buffer and store at m_callbackBuffer
				m_bufConverter.getBuffer(m_callbackBuffer, &incomingSamples);
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


void EffectsManager::applyEffect(ChannelSamples* final_data, ChannelSamples* initial_data)
{
	// For each effect stored
	for (auto it = m_activeEffects.begin(); it != m_activeEffects.end(); ++it)
	{
		// For each frame
		for (uint16_t sampleIndx = 0; sampleIndx < initial_data->getFramesCount(); ++sampleIndx)
		{
			// Apply effect to both samples within frame
			final_data->insertLeft(sampleIndx, (*it)->applyEffect(initial_data->getLeftElement(sampleIndx)));
			final_data->insertRight(sampleIndx, (*it)->applyEffect(initial_data->getRightElement(sampleIndx)));
		}
	}
}


void EffectsManager::alterEffect(EffectBase* effect, ParamIndx parameter, int32_t new_val)
{
	return; // Placeholder
}
