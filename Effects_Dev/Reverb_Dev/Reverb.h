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
	
	float delayMS;
	float decay;
	std::vector<double> coefficients;
	std::unique_ptr<Fir1> delayLinePtr;

	enum params {
		delayParam = 1,
		decayParam = 2,
		} params;
		
	std::vector<double> createCoeffs(int32_t taps){
		for (unsigned int i=0; i < taps-1; i++){
			coefficients.push_back(0);
		}
	coefficients.push_back(1);
	return coefficients;
	}


	Reverb(){
		delayMS = 100;
		decay = 0.2;
		int delaySample = delayMS * 0.001 * sampleRate; //Calculates delay based on samplerate	

		delayLinePtr.reset(new Fir1 (createCoeffs(delaySample)));
	};

	
	int32_t applyEffect(int32_t current_sample) override;

	void changeParam(int32_t param, float val) override;
		

private:
};

#endif
