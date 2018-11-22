#pragma once
#ifndef __OSCILLATOR__
#define __OSCILLATOR__
#include <math.h>
#include "IPlugStructs.h"


class Oscillator {
private:
	bool isActive;
	bool isHold;
	double mFrequency;
	double mPhase;
	double mDivision;
	double mPhaseLength;
	double mSampleRate;
	double rawOutput;
	double output;
	const double smoothFactor = 0.01;
	double mixA;
	double mixB;

public:
	void setFrequency(double frequency);
	inline void setActive(bool muted) { isActive = muted; }
	inline void setHold(bool hold) { isHold = hold; }
	inline void resetPhase() { mPhase = 0; }
	void setChopper(double division, double sampRate);
	double nextSample(double tempo);
	double smooth(double value);
	void updateMix(double mix);
	Oscillator() :
		isActive(false),
		isHold(false),
		mFrequency(0.0),
		mPhase(0.0),
		rawOutput(1.0),
		output(1.0),
		mixA(1.0),
		mixB(0.0) {
		;
	}
};

#endif