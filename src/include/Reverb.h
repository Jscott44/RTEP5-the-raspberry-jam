#include "EffectBase.h"

#ifndef DISTORTION_H
#define DISTORTION_H

#include <cstdint>
#include <iostream>
#include <memory>
#include "Fir1.h"

class Reverb : public EffectBase
{
public:
	Reverb();
	std::vector<double> createCoeffs(int32_t taps);

	int32_t applyEffect(int32_t current_sample) override;
	void alterEffect(ParamIndx parameter, float new_val) override;
private:
	float m_delayMS;
	float m_decay;
	int32_t m_sampleRate;
	std::vector<double> m_coefficients;
	std::unique_ptr<Fir1> m_delayLinePtr;
};

#endif
