#include "EffectBase.h"

#ifndef DISTORTION_H
#define DISTORTION_H

class Distortion : public EffectBase
{
public:
	Distortion();
	~Distortion();
	int32_t applyEffect(int32_t current_sample) override;
private:
};

#endif
