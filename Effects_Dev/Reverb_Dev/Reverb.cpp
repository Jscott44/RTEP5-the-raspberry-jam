#include "Reverb.h"
#include <filesystem>

int32_t Reverb::applyEffect(int32_t current_sample)
{
	// Put your data processing
	double tempVal = current_sample/pow(2, 31) + decay * delayLinePtr->filter(current_sample/pow(2, 31));
	
	int32_t retVal = tempVal * pow(2, 31);

	return retVal;
}

void Reverb::changeParam(int32_t param, float val){		
		switch(param) {
			case 1:
				delayMS = val;
				break;
			case 2:
				decay = val;
				break;
		}
}

