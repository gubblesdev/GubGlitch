#pragma once
#ifndef __STUTTER__
#define __STUTTER__
#include <math.h>
#include "IPlugStructs.h"

class Stutter {
private:
	double* deck;
	double deckLength;

public:
	void setLength(double tempo, double division, double sampleRate);
	double process(double input);
	Stutter();
};

#endif