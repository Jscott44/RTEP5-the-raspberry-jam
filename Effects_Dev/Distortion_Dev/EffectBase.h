#ifndef EFFECTBASE_H
#define EFFECTBASE_H
#include <cstdint>
#include <cmath>


class EffectBase
{
public:
	double volume;
	

	EffectBase(){
		volume = 0.2;
	}; // Placeholder
	virtual int32_t applyEffect(int32_t current_sample) = 0; // Dario Note: Override this method when you want to add effect in children classes

	virtual void changeParam(int32_t param, float val) = 0;
		//enum to the prameter and a value to change it to
private:
};

#endif
