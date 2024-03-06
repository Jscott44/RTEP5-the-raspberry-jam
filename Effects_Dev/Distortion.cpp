#include "Distortion.h"
#include "sine_wave_gen/AudioFile.h"
#include <filesystem>

int32_t Distortion::applyEffect(int32_t current_sample)
{
	// Put your data processing
	
	int32_t retVal =  tanh(current_sample * Distortion::gain) * Distortion::volume;
	
	return retVal;
}

void Distortion::changeParam(int32_t param, int32_t val){		
		switch(param) {
			case 1:
				gain = val;
				break;
		}
}

int main()
{
	AudioFile<float> sinWave;


	sinWave.load(std::string (std::filesystem::current_path()) + "___middle_a.wav");

	Distortion distort;
	
	std::cout << distort.gain << std::endl;

	distort.changeParam(distort.gainParam ,2);

	std::cout << distort.gain << std::endl;

	//for(auto i : distort.params){
	//	distort.changeParams(i, get_val(slider));
	//}
	//
	distort.changeParam(distort.gainParam, 14);

	std::cout << distort.gain << std::endl;
	
	
        for (int i = 0; i < sinWave.getNumSamplesPerChannel(); i++)
        {
            for (int channel = 0; channel < sinWave.getNumChannels(); channel++)
            {
                sinWave.samples[channel][i] = distort.applyEffect(sinWave.samples[channel][i]);
            }
        }
	
	sinWave.save(std::string (std::filesystem::current_path()) + "middle_a_distorted.wav");

}
