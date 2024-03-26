 #ifndef EFFECTBASE_H
#define EFFECTBASE_H
#include <cstdint>
#include <cmath>

enum EffectIndx
{
	DistortionIndx = 0,
	ReverbIndx
};

enum ParamIndx
{
	eVolume = 0,
	eGain,
	eDelayMs,
	eDecay
};



class EffectBase
{
public:
	//EffectBase() ; // Placeholder
	//~EffectBase(); // Placeholder
	virtual int32_t applyEffect(int32_t current_sample) = 0; // Dario Note: Override this method when you want to add effect in children classes
	virtual void alterEffect(ParamIndx parameter, float new_val) = 0;
protected:
	float m_volume = 1;
};



// // PLACEHOLDERS UNTIL WE MERGE WITH EFFECTS_DEV
// class Distortion : public EffectBase 
// {
// 	int32_t applyEffect(int32_t current_sample) override
// 	{
// 		return current_sample * m_volume;
// 	}

// 	void alterEffect(ParamIndx parameter, float new_val)
// 	{
// 		// Will need a switch statement here to alter the desired parameters for this class
// 		m_volume = new_val;
// 		return;
// 	}
// };
// class Reverb : public EffectBase 
// {
// 	int32_t applyEffect(int32_t current_sample) override
// 	{
// 		return current_sample * m_volume;
// 	}

// 	void alterEffect(ParamIndx parameter, float new_val)
// 	{
// 		m_volume = new_val;
// 		return;
// 	}
// };

#endif