#ifndef REVERB_H
#define REVERB_H

#include "EffectBase.h"
#include <cstdint>
#include <iostream>
#include <memory>
//#include "Fir1.h"
#include <vector>

class Reverb : public EffectBase
{
public:
	Reverb();
	int32_t applyEffect(int32_t current_sample) override;
	void alterEffect(ParamIndx parameter, float new_val) override;

	std::vector<float> delaylineBuff;
	int32_t writeIndex;

private:
	float m_delayMS;
	float m_decay;
	int32_t m_sampleRate;

};
//public:
//	Reverb();
//	std::vector<double> createCoeffs(int32_t taps);
//
//	int32_t applyEffect(int32_t current_sample) override;
//	void alterEffect(ParamIndx parameter, float new_val) override;
//private:
//	float m_delayMS;
//	float m_decay;
//	int32_t m_sampleRate;
//	std::vector<double> m_coefficients;
//	std::unique_ptr<Fir1> m_delayLinePtr;
//};

#endif
