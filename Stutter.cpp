#include "Stutter.h"
#include "IPlug/IPlug_include_in_plug_hdr.h"


Stutter::Stutter() {

}

void Stutter::setLength(double tempo, double division, double sampleRate) {
	// Calculate how many samples long the deck should be
	// Integer division truncates remainder; determine whether or not this is desirable behavior
	deckLength = ((tempo / 60) / division) * sampleRate;		// Subtract 1 because first index of array is 0?
	c = 0;
	isFull = false;
}

double Stutter::process(double input) {
	
	if (c > deckLength) {
		c = 0;
	}

	// Fill the stutter deck until it's full
	if (!isFull) {
		deck[c] = input;
		c++;
		if (c > deckLength)
			isFull = true;
		return input;
	}
	// Loop the deck after it's been filled
	else {
		stage = deck[c];
		c++;
		return stage;
	}
}
