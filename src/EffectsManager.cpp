#include "include/EffectsManager.h"
#include <stdio.h>


/// @brief Object can be used to process samples. Implements GUI and Alsa callbacks.
EffectsManager::EffectsManager(eEndianness endian, uint8_t bytes_per_sample, uint16_t frames_per_buffer)
	:	GuiListener(),
		AlsaListener(),
		m_bufConverter(endian, bytes_per_sample, frames_per_buffer),
		m_incomingSamples(new ChannelSamples(m_bufConverter.getFramesPerBuffer())),
		m_outgoingSamples(new ChannelSamples(m_bufConverter.getFramesPerBuffer())),
		m_newBuffer(false),
		m_running(false)
{
	// Reserve some memory to make it more effecient 
	m_activeEffects.reserve(10);

	// Indicates whether the GUI is attempting to access the effects
	m_alteringEffects = false;

	// Allocate callback buffer on heap
	uint16_t callbackBufferSize = m_bufConverter.getFramesPerBuffer() * m_bufConverter.getSamplesPerFrame() * m_bufConverter.getBytesPerSample();
	m_callbackBuffer = new uint8_t[callbackBufferSize];

	// Initialise thread. Won't start until it receives first signal from callback
	m_running = true;
	m_thread = new std::thread(&EffectsManager::effectLoop, this);
}

/// @brief Safely stops thread before deleting all members.
EffectsManager::~EffectsManager()
{
	printf("entering em stop\n");

	// Stop thread
	m_running = false;

	// Wait for thread to safely terminate
	m_thread->join();

	// Delete thread
	delete m_thread;
	m_thread = nullptr;

	// Delete ChannelSamples
	delete m_incomingSamples;
	m_incomingSamples = nullptr;
	delete m_outgoingSamples;
	m_outgoingSamples = nullptr;

	// Delete buffer
	delete[] m_callbackBuffer;
	m_callbackBuffer = nullptr;
}

/// @brief Register object that will handle callbacks after data is processed.
/// @param callback_ptr Object that implements callback.
void EffectsManager::registerCallback(EffectListener* callback_ptr)
{
	m_callbackPtr = callback_ptr;
}

/// @brief From AlsaListener. Stores buffer reference to be used by EffectsManager.
/// @param buffer Buffer reference that should be used.
void EffectsManager::hasBuffer(uint8_t* buffer)
{
	// Store pointer to buffer
	m_listenerBuffer = buffer;

	// Unblock effect loop to process data that has been transfered
	m_newBuffer = true;

}

/// @brief Processes buffer obtained and passes processed buffer to next object using callback.
void EffectsManager::effectLoop()
{
	//printf("Entering effect loop\n");

	while (m_running) // Turn false to stop
	{	
		// If new buffer has been received
		if (m_newBuffer)
		{
			printf("n\n"); // DEBUG

			// Reset to wait for next callback
			m_newBuffer = false;

			// Convert buffer into ChannelSamples object
			m_bufConverter.getSamples(m_incomingSamples, m_listenerBuffer);

			//printf("%02X\n", m_listenerBuffer[0]);

			//printf("l: %d \tr: %d\n", m_incomingSamples->getLeftElement(0), m_incomingSamples->getRightElement(0));

			// If GUI is currently not adjusting effects
			if (!m_alteringEffects)
			{
				// Apply effects
				applyEffect(m_outgoingSamples, m_incomingSamples);

				//printf("l: %d \tr: %d\n", m_outgoingSamples->getLeftElement(0), m_outgoingSamples->getRightElement(0));

				// Convert processed ChannelSamples struct back into buffer
				m_bufConverter.getBuffer(m_callbackBuffer, m_outgoingSamples);
			}
			else
			{
				// Convert original ChannelSamples struct back into buffer (bypasses effects)
				m_bufConverter.getBuffer(m_callbackBuffer, m_incomingSamples);
			}

			//printf("%02X\n", m_callbackBuffer[0]);
			// Trigger callback
			m_callbackPtr->hasAlteredBuffer(m_callbackBuffer);
		}
	}
}


/// @brief Add effect that should be used when processing samples.
/// @param desired_effect Enum of effect that should be added.
/// @return Ptr should be used when attempting to access effect with any other GuiListener method.
EffectBase* EffectsManager::addEffect(EffectIndx desired_effect)
{
	// Tell this that it is not allowed to apply effects in effectLoop
	m_alteringEffects = true;

	// Init pointer that will be returned
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

	// Tell this that is is allowed to apply effects again
	m_alteringEffects = false;

	// Return pointer to new object
	return retPtr;
}

/// @brief Removes effect being used to process samples.
/// @param effect Ptr to effect that should be removed.
void EffectsManager::removeEffect(EffectBase* effect)
{
	// Tell object that it is not allowed to apply effects
	m_alteringEffects = true;

	bool effectRemoved = false;

	// Loop through all stored effects
	for (auto it = m_activeEffects.begin(); it != m_activeEffects.end(); ++it)
	{
		if (effect == *it) // If the effect given in the method argument == a stored method, delete it
		{
			delete* it;
			*it = nullptr;
			m_activeEffects.erase(it);
			effectRemoved = true;
			break;
		}
	}

	if (!effectRemoved)
	{
		printf("Effect was not found and could not be removed. Throwing...\n");
		throw;
	}

	// Tell object that it is allowed to apply effects
	m_alteringEffects = false;
}


/// @brief Processes all samples using the registered effects.
/// @param final_data RETURN. Object containing processed samples.
/// @param initial_data Object containing samples that should be processed.
void EffectsManager::applyEffect(ChannelSamples* final_data, ChannelSamples* initial_data)
{
	printf("%d", m_activeEffects.size());

	// No point going into loop if we have no effects
	if (m_activeEffects.size() == 0)
	{
		// For each frame
		for (uint16_t sampleIndx = 0; sampleIndx < initial_data->getFramesCount(); ++sampleIndx)
		{
			// Move data from initial to final
			final_data->insertLeft(sampleIndx, initial_data->getLeftElement(sampleIndx));
			final_data->insertRight(sampleIndx, initial_data->getRightElement(sampleIndx));
		}
		return;
	}

	// For each effect stored
	for (auto it = m_activeEffects.begin(); it != m_activeEffects.end(); ++it)
	{
		// For each frame
		for (uint16_t sampleIndx = 0; sampleIndx < initial_data->getFramesCount(); ++sampleIndx)
		{
			// Apply effect to the samples for each channel
			final_data->insertLeft(sampleIndx, (*it)->applyEffect(initial_data->getLeftElement(sampleIndx)));
			final_data->insertRight(sampleIndx, (*it)->applyEffect(initial_data->getRightElement(sampleIndx)));
		}
	}
}

// TODO: Implement alterEffect
/// @brief 
/// @param effect 
/// @param parameter 
/// @param new_val 
void EffectsManager::alterEffect(EffectBase* effect, ParamIndx parameter, float new_val)
{
	// Tell object that it is not allowed to apply effects
	m_alteringEffects = true;

	// Loop through all stored effects
	for (auto it = m_activeEffects.begin(); it != m_activeEffects.end(); ++it)
	{
		if (effect == *it) // If the effect given in the method argument == a stored method, delete it
		{
			(*it)->alterEffect(parameter, new_val);
		}
	}

	return; // Placeholder
}
