#include "Reverb.h"

Reverb::Reverb()
	: m_delayMS(100),
	  m_decay(0.2),
	  m_delayLinePtr(new Fir1(createCoeffs(m_delayMS * 0.001 * m_sampleRate))) //Calculates delay based on samplerate	
{
}

std::vector<double> Reverb::createCoeffs(int32_t taps)
{
	for (unsigned int i=0; i < taps-1; i++)
	{
		m_coefficients.push_back(0);
	}
	m_coefficients.push_back(1);
	return m_coefficients;
}

int32_t Reverb::applyEffect(int32_t current_sample)
{
	double tempVal = current_sample/pow(2, 31) + m_decay * m_delayLinePtr->filter(current_sample/pow(2, 31));
	int32_t retVal = tempVal * pow(2, 31);
	return retVal;
}

void Reverb::alterEffect(ParamIndx parameter, float new_val)
{
	switch(parameter) {
		case eVolume:
			m_volume = new_val;
			break;
		case eGain:
			// No Gain
			break;
		case eDelayMs:
			m_delayMS = new_val;
			break;
		case eDecay:
			m_decay = new_val;
	}
}

