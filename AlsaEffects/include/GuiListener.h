#ifndef GUILISTENER_H
#define GUILISTENER_H

#include "EffectBase.h"

class GuiListener
{
public:
	GuiListener();
	~GuiListener();

	virtual EffectBase* addEffect(EffectIndx desired_effect) = 0;
	virtual void removeEffect(EffectBase* effect) = 0;
	virtual void alterEffect(EffectBase* effect, ParamIndx parameter, int32_t new_val) = 0;

protected:
	bool m_alteringEffects;
};


#endif // !GUILISTENER_H
