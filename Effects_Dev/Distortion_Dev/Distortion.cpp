#include "Distortion.h"
#include <filesystem>

int32_t Distortion::applyEffect(int32_t current_sample)
{
	// Put your data processing
	
	
	double tempVal =  (tanh(current_sample/pow(2, 31) * Distortion::gain) * Distortion::volume);
	int32_t retVal = tempVal * pow(2, 31);

	
	return retVal;
}

void Distortion::changeParam(int32_t param, float val){		
		switch(param) {
			case 1:
				gain = val;
				break;
		}
}




























