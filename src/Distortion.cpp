#include "Distortion.h"
#include <filesystem>

Distortion::Distortion()
	:	m_gain(1)
{

}

int32_t Distortion::applyEffect(int32_t current_sample)
{
	double tempVal =  (tanh(current_sample/pow(2, 31) * m_gain) * m_volume);
	int32_t retVal = tempVal * pow(2, 31);
	return retVal;
}

void Distortion::alterEffect(ParamIndx parameter, float new_val){		
	switch(parameter) 
	{
	case eVolume:
		m_volume = new_val;
		break;
	case eGain:
		m_gain = new_val;
		break;
	case eDelayMs:
		// No delay
		break;
	case eDecay:
		// No decay
	default:
		break;
	}
}




























