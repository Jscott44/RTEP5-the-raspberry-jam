 #ifndef EFFECTBASE_H
#define EFFECTBASE_H
#include <cstdint>

enum EffectIndx
{
	DistortionIndx = 0,
	ReverbIndx
};

enum ParamIndx
{
	eVolume = 0,
	eGain
};



class EffectBase
{
public:
	//EffectBase() ; // Placeholder
	//~EffectBase(); // Placeholder
	virtual int32_t applyEffect(int32_t current_sample) = 0; // Dario Note: Override this method when you want to add effect in children classes
	virtual void alterEffect(ParamIndx parameter, float new_val) = 0;
private:
	float m_volume = 0;
};



// PLACEHOLDERS UNTIL WE MERGE WITH EFFECTS_DEV
class Distortion : public EffectBase 
{
	int32_t applyEffect(int32_t current_sample) override
	{
		return current_sample / 2;
	}

	void alterEffect(ParamIndx parameter, float new_val)
	{
		// Will need a switch statement here to alter the desired parameters for this class
		return;
	}
};
class Reverb : public EffectBase 
{
	int32_t applyEffect(int32_t current_sample) override
	{
		return current_sample;
	}

	void alterEffect(ParamIndx parameter, float new_val)
	{
		return;
	}
};

#endif