#ifndef ALSAEFFECTS_H
#define ALSAEFFECTS_H

#include <condition_variable>
#include <mutex>
#include <thread>
#include "SafeQueue.h"
#include "EffectsManager.h"
#include "AlsaBufferConverter.h"


class AlsaEffects
{
public:
	AlsaEffects();
	~AlsaEffects();

	void start();
	// Add more methods to allow GUI to interact in the future
private:
	void captureLoop();
	void processLoop();
	void playbackLoop();

	std::thread* m_captureThread;
	std::thread* m_processThread;
	std::thread* m_playbackThread; 

	SafeQueue m_toProcess;
	SafeQueue m_toPlayback;

	bool m_loopsRunning;

	AlsaBufferConverter m_converter;
	EffectsManager m_effectsManager;
};

#endif