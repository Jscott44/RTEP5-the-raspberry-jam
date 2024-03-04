#ifndef EFFECTBASE_H
#define EFFECTBASE_H
#include <cstdint>

enum EffectIndx
{
	DistortionIndx = 0,
	ReverbIndx
};

class EffectBase
{
public:
	//EffectBase() ; // Placeholder
	//~EffectBase(); // Placeholder
	virtual int32_t applyEffect(int32_t current_sample) = 0; // Dario Note: Override this method when you want to add effect in children classes
private:
	int32_t volume = 0;
};



// PLACEHOLDERS UNTIL WE MERGE WITH EFFECTS_DEV
class Distortion : public EffectBase 
{
	int32_t applyEffect(int32_t current_sample) override
	{
		return current_sample / 2;
	}
};
class Reverb : public EffectBase 
{
	int32_t applyEffect(int32_t current_sample) override
	{
		return current_sample;
	}
};

#endif