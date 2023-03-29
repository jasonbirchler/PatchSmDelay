/*
Daisy PatchSM skeleton program based on
https://github.com/algoritmarte/algodaisy
*/
#include "daisy_patch_sm.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;
using namespace patch_sm;

DaisyPatchSM hw;
bool gateOut1 = false;
float cv1_volt = 0;
float cv2_volt = 0;
bool encoder_held;
bool encoder_press;    
int encoder_inc;
float last_cv1_volt = -1;
float last_cv2_volt = -1;

float knobValues[4] = {};

float audioSampleRate;
float cvSampleRate;

const int notes[8] = { 0,2,4,5,7,9,11,12};
int inote = 0;
float freq = 440.0;
int notetick = 0;
int encoder_track = 0;

WhiteNoise noise;
Oscillator osc;

void UpdateControls();

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	UpdateControls();

	// prepare freq for AUDIO1
	float midinote = 60 + notes[ inote ];
	float freq = 440.0f * pow( 2, (midinote - 69) / 12.0f );
	osc.SetFreq( freq );
	osc.SetAmp( knobValues[0] ); // keep it on LINE level

	for (size_t i = 0; i < size; i++)
	{
		// sine wave on AUDIO1
		out[0][i] = osc.Process();

		// white noise on AUDIO2
		out[1][i] = noise.Process() * knobValues[1]; // keep it on LINE levels
	}
}

int main(void)
{
	hw.Init();
	//hw.SetAudioBlockSize(32); // if needed (default 48 )

	audioSampleRate = hw.AudioSampleRate();
	cvSampleRate = audioSampleRate / hw.AudioBlockSize();

	noise.Init();
	osc.Init(audioSampleRate);

	hw.StartAdc();
	hw.StartAudio(AudioCallback);
	while(1) {
	}
}

void UpdateControls() {
	// needed for properly reading hardware
	hw.ProcessAllControls();

	knobValues[0] = hw.GetAdcValue( CV_1 );
	knobValues[1] = hw.GetAdcValue( CV_2 );
	knobValues[2] = hw.GetAdcValue( CV_3 );
	knobValues[3] = hw.GetAdcValue( CV_4 );						  
}
