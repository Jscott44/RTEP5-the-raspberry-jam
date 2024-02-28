#include "Distortion.h"


int32_t Distortion::applyEffect(int32_t current_sample)
{
	// Put your data processing
	
	int32_t retVal =  tanh(current_sample * Distortion::gain) * Distortion::volume;
	
	return retVal;
}

int main()
{
	Distortion distort(2);
	printf("compiled");
	
}
