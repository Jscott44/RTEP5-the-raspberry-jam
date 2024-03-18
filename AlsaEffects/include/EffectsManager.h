#ifndef EFFECTSMANAGER_H
#define EFFECTSMANAGER_H
#include <cstdint>
#include <vector>
#include <thread>
#include "EffectBase.h"
#include "AlsaBufferConverter.h"

// Thread safe interactions
#include "ThreadBlocker.h"

// Will trigger callback
#include "AlsaListener.h"
#include "GuiListener.h"

// Will use callback from this
#include "EffectListener.h"

class EffectsManager : public AlsaListener , public GuiListener
{
public:
	EffectsManager(); // Placeholder
	~EffectsManager(); // Placeholder

	void registerCallback(EffectListener* callback_ptr);

	// Gui Listener Methods
	EffectBase* addEffect(EffectIndx desired_effect) override;
	void removeEffect(EffectBase* effect) override;
	void alterEffect(EffectBase* effect, ParamIndx parameter, int32_t new_val) override;

	// Alsa Listener Methods
	void hasBuffer(uint8_t* buffer) override;

private:
	ChannelSamples applyEffect(ChannelSamples initial_data);

	void effectLoop();

	AlsaBufferConverter m_bufConverter;
	EffectListener* m_callbackPtr;
	uint8_t* m_callbackBuffer;

	ThreadBlocker m_threadInterface;

	bool m_running;
	std::vector<EffectBase*> m_activeEffects;
	std::thread* m_effectThread;
};

#endif