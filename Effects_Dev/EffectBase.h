#ifndef EFFECTBASE_H
#define EFFECTBASE_H
#include <cstdint>

class EffectBase
{
public:
	int32_t volume;
	EffectBase(){
		volume = 0;
	}; // Placeholder
	//~EffectBase(); // Placeholder
	virtual int32_t applyEffect(int32_t current_sample) = 0; // Dario Note: Override this method when you want to add effect in children classes
private:
};

#endif
