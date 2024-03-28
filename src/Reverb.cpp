#include "Reverb.h"

Reverb::Reverb()
	: m_delayMS(100),
	  m_decay(0.2),
	  m_sampleRate(96000)
{
	int delaySample = m_delayMS * 0.001 * m_sampleRate;
	delaylineBuff.resize(delaySample + 1);
	for(int i = 0; i < delaylineBuff.size(); i++){
		delaylineBuff[i] = 0;
	}
	writeIndex = 0;
}


int32_t Reverb::applyEffect(int32_t current_sample)
{
	int32_t currentReading = delaylineBuff[writeIndex];
	double tempVal = current_sample/pow(2, 31) + m_decay * currentReading/pow(2, 31);
	int32_t retVal = tempVal * pow(2, 31);
	delaylineBuff[writeIndex] = retVal;//FOR DELAY REPLACE RETVAL WITH CURRENT_SAMPLE
	writeIndex = (writeIndex + 1) % delaylineBuff.size();
	return retVal;
}

void delayline::alterEffect(ParamIndx parameter, float new_val)
{
	switch(parameter) {
		case eVolume:
			m_volume = new_val;
			break;
		case eGain:
			// No Gain
			break;
		case eDelayMs:
			{
			int32_t old_val = delaylineBuff.size();
			int32_t m_delaySample = new_val*0.001*m_sampleRate;
			delaylineBuff.resize(m_delaySample + 1);
			if (old_val < m_delaySample) {
				for (int i=old_val; i<m_delaySample+1;i++) {
					delaylineBuff[i]=0;
				}
			}
			break;
			}
		case eDecay:
			m_decay = new_val;
	}
}

//Reverb::Reverb()
//	: m_delayMS(2),
//	  m_decay(0.8), 
//	  m_sampleRate(96000)
//{
//	int delaySample = m_delayMS * 0.001 * m_sampleRate;
//	m_delayLinePtr.reset(new Fir1(createCoeffs(delaySample)));
//}
//
//std::vector<double> Reverb::createCoeffs(int32_t taps)
//{
//	for (unsigned int i=0; i < taps-1; i++)
//	{
//		m_coefficients.push_back(0);
//	}
//	m_coefficients.push_back(1);
//	return m_coefficients;
//}
//
//int32_t Reverb::applyEffect(int32_t current_sample)
//{
//	double tempVal = current_sample/pow(2, 31) + m_decay * m_delayLinePtr->filter(current_sample/pow(2, 31));
//	int32_t retVal = tempVal * pow(2, 31);
//	return retVal;
//}

//void Reverb::alterEffect(ParamIndx parameter, float new_val)
//{
//	switch(parameter) {
//		case eVolume:
//			m_volume = new_val;
//			break;
//		case eGain:
//			// No Gain
//			break;
//		case eDelayMs:
//			m_delayMS = new_val;
//			break;
//		case eDecay:
//			m_decay = new_val;
//	}
//}




