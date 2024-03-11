#include "Distortion.h"
#include "sine_wave_gen/AudioFile.h"
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

int main()
{
	AudioFile<int32_t> sinWave;

	sinWave.load("voice_recording.wav");

	Distortion distort;
	
	std::cout << distort.gain << std::endl;

	distort.changeParam(distort.gainParam ,50);

	std::cout << distort.gain << std::endl;

        for (int i = 0; i < sinWave.getNumSamplesPerChannel(); i++)
        {
            for (int channel = 0; channel < sinWave.getNumChannels(); channel++)
            {
		//std::cout << sinWave.samples[channel][i] << std::endl;
                sinWave.samples[channel][i] = distort.applyEffect(sinWave.samples[channel][i]);
		//std::cout << sinWave.samples[channel][i] << std::endl;
            }
        }
	
	sinWave.save("voice_distorted.wav");

}
