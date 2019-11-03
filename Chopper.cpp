#include "Chopper.h"
#include "IPlug/IPlug_include_in_plug_hdr.h"
#include "math.h"


void Chopper::setFrequency(double division) {
	cFrequency = gTempo * division / 480.0;
}

void Chopper::setChopper(double division) {
	cDivision = division;
	setActive(true);
	resetPhase();
}

void Chopper::updateMix(double mix) {

	// Scale range of values from -1.0 to 1.0
	mix = mix / 100.0;

	// TO DO : Check if this scaling is indeed logarithmic? I think it is??
	if (mix > 0.0) {
		mixA = 1.0;
		mixB = pow(-mix + 1.0, 6);
	}
	else if (mix < 0.0) {
		mixA = pow(mix + 1.0, 6);
		mixB = 1.0;
	}
	else mixA = mixB = 1.0;

}

// Smooth any output values to prevent pops and clicks
double Chopper::smooth(double value) {

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


double Chopper::nextSample() {

	if (isHold) {
		rawOutput = 0.0;
		return smooth(output);
	}
	if (!isActive) {
		rawOutput = 1.0;
		return smooth(output);
	}

	// Update the tempo every sample to account for tempo jumps, ramps, etc.
	setFrequency(cDivision);
	cPhaseLength = 1 / cFrequency * gSampleRate;

	// Generate square wave
	if (cPhase <= (cPhaseLength / 2)) {
		rawOutput = mixA;
	}
	else {
		rawOutput = mixB;
	}

	// Advance phase each sample
	cPhase++;
	while (cPhase >= cPhaseLength) {
		cPhase -= cPhaseLength;
	}

	return smooth(output);
}