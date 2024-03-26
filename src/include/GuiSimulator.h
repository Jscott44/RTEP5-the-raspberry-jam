#ifndef GUISIMULATOR_H
#define GUISIMULATOR_H 

#include "EffectBase.h"
#include "GuiListener.h"

class GuiSimulator
{
public:
    void registerCallback(GuiListener* ptr);

	EffectBase* addEffect(EffectIndx desired_effect);
	void removeEffect(EffectBase* effect);
	void alterEffect(EffectBase* effect, ParamIndx parameter, int32_t new_val);
private:
    GuiListener* m_callbackPtr;
};



#endif