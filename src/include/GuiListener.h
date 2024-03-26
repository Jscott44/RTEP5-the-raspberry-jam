#ifndef GUILISTENER_H
#define GUILISTENER_H

#include "EffectBase.h"
#include <cstdint>

class GuiListener
{
public:
	virtual EffectBase* addEffect(EffectIndx desired_effect) = 0;
	virtual void removeEffect(EffectBase* effect) = 0;
	virtual void alterEffect(EffectBase* effect, ParamIndx parameter, float new_val) = 0;

protected:
	bool m_alteringEffects;
};


#endif // !GUILISTENER_H
