#ifndef DISTORTION_H
#define DISTORTION_H

#include "EffectBase.h"
#include <cstdint>
#include <iostream>

class Distortion : public EffectBase
{
public:
	Distortion();
	int32_t applyEffect(int32_t current_sample) override;
	void alterEffect(ParamIndx parameter, float new_val) override;
private:
	float m_gain;
};

#endif
