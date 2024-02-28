#include "EffectBase.h"

#ifndef DISTORTION_H
#define DISTORTION_H

#include <cmath>
#include <cstdint>
#include <iostream>

class Distortion : public EffectBase
{
public:
	int32_t gain;

	Distortion(int32_t Gain){
	gain = Gain;
	};

	//~Distortion();
	
	int32_t applyEffect(int32_t current_sample) override;
private:
};

#endif
