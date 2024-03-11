#include "EffectBase.h"

#ifndef DISTORTION_H
#define DISTORTION_H

//#include <cmath>
#include <cstdint>
#include <iostream>

class Distortion : public EffectBase
{
public:
	
	//std::map<std::string, int32_t> params;


	int32_t gain;

	enum params {
		gainParam = 1,
		} params;
		

	Distortion(){
		gain = 1;
	
	};

	//~Distortion();
	
	int32_t applyEffect(int32_t current_sample) override;

	void changeParam(int32_t param, float val) override;
		

private:
};

#endif
