#pragma once
#ifndef __OSCILLATOR__
#define __OSCILLATOR__
#include <math.h>
#include "IPlugStructs.h"

extern double gTempo;
extern double gSampleRate;

class Oscillator {
private:
	bool isActive;
	bool isHold;
	double cFrequency;
	double cPhase;
	double cDivision;
	double cPhaseLength;
	double rawOutput;
	double output;
	const double smoothFactor = 0.01;
	double mixA;
	double mixB;

public:
	void setFrequency(double division);
	inline void setActive(bool muted) { isActive = muted; }
	inline void setHold(bool hold) { isHold = hold; }
	inline void resetPhase() { cPhase = 0; }
	void setChopper(double division);
	double nextSample();
	double smooth(double value);
	void updateMix(double mix);
	Oscillator() :
		isActive(false),
		isHold(false),
		cFrequency(0.0),
		cPhase(0.0),
		rawOutput(1.0),
		output(1.0),
		mixA(1.0),
		mixB(0.0) {
		;
	}
};

#endif