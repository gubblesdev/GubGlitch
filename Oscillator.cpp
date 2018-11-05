#include "Oscillator.h"
#include "IPlug/IPlug_include_in_plug_hdr.h"
#include "math.h"


void Oscillator::setFrequency(double frequency) {
	mFrequency = frequency;
}

void Oscillator::setSampleRate(double sampleRate) {
	mSampleRate = sampleRate;
}

void Oscillator::setChopper(double division) {
	mDivision = division;
	setActive(true);
	resetPhase();
}

void Oscillator::updateMix(double mix) {

	//Scale range of values from -1.0 to 1.0
	mix = mix / 100.0;

	if (mix > 0.0) {
		mixA = 1.0;
		mixB = 1.0 - mix;
	}
	else if (mix < 0.0) {
		mixA = 1.0 + mix;
		mixB = 1.0;
	}
	else mixA = mixB = 1.0;

}

// Smooth any output values to prevent pops and clicks
double Oscillator::smooth(double value) {

	if (value < rawOutput) {
		// If smoothing brings value above the threshold, snap down to target
		if (value + smoothFactor > rawOutput) {
			value = rawOutput;
		}
		else value += smoothFactor;
	}
	else if (value > rawOutput) {
		// If smoothing brings value below threshold, snap up to target
		if (value - smoothFactor < rawOutput) {
			value = rawOutput;
		}
		else value -= smoothFactor;
	}
	output = value;
	return output;
}


double Oscillator::nextSample(double tempo, double mix) {

	if (isHold) {
		rawOutput = 0.0;
		return smooth(output);
	}
	if (!isActive) {
		rawOutput = 1.0;
		return smooth(output);
	}

	// Update the tempo every sample to account for tempo jumps, ramps, etc.
	// Costly to do every update, but I dunno how else to account for this
	setFrequency(tempo * mDivision / 480.0);
	mPhaseLength = 1 / mFrequency * mSampleRate;

	// Generate square wave
	if (mPhase <= (mPhaseLength / 2)) {
		rawOutput = mixA;
	}
	else {
		rawOutput = mixB;
	}

	// Advance phase each sample
	mPhase++;
	while (mPhase >= mPhaseLength) {
		mPhase -= mPhaseLength;
	}

	return smooth(output);
}