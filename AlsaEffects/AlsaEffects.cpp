#include "include/AlsaEffects.h"

AlsaEffects::AlsaEffects()
	: m_captureThread(nullptr),
	m_processThread(nullptr),
	m_playbackThread(nullptr),
	m_loopsRunning(false)
{

}

AlsaEffects::~AlsaEffects()
{
	if (m_captureThread != nullptr)
	{
		delete m_captureThread;
		m_captureThread = nullptr;
	}
	if (m_processThread != nullptr)
	{
		delete m_processThread;
		m_processThread = nullptr;
	}
	if (m_playbackThread != nullptr)
	{
		delete m_playbackThread;
		m_playbackThread = nullptr;
	}
}

void AlsaEffects::start()
{
	if (m_captureThread == nullptr)
	{
		m_captureThread = new std::thread(&AlsaEffects::captureLoop, this);
	}
	if (m_processThread == nullptr)
	{
		m_processThread = new std::thread(&AlsaEffects::processLoop, this);
	}
	if (m_playbackThread == nullptr)
	{
		m_playbackThread = new std::thread(&AlsaEffects::playbackLoop, this);
	}
}


void AlsaEffects::captureLoop()
{
	while (m_loopsRunning)
	{
		// PCM Device READ method (blocking)

		std::shared_ptr<uint8_t> dataBuffer = nullptr; // PLACEHOLDER: Need to convert buffer that has been read into a shared ptr

		m_toProcess.setBuffer(dataBuffer);
	}
}
void AlsaEffects::processLoop()
{
	while (m_loopsRunning)
	{
		std::shared_ptr<uint8_t> incomingBuffer = m_toProcess.getBuffer(); //Blocking

		ChannelSamples incomingSamples = m_converter.getSamples(incomingBuffer.get());

		ChannelSamples outgoingSamples = m_effectsManager.applyEffect(incomingSamples);

		std::shared_ptr<uint8_t> outgoingBuffer = m_converter.getBuffer(outgoingSamples);

		m_toPlayback.setBuffer(outgoingBuffer);
	}
}
void AlsaEffects::playbackLoop()
{
	while (m_loopsRunning)
	{
		std::shared_ptr<uint8_t> dataBuffer = m_toPlayback.getBuffer(); //Blocking

		// PCM Device WRITE method
	}
}