#include "Stutter.h"
#include "IPlug/IPlug_include_in_plug_hdr.h"


Stutter::Stutter() {

}

void Stutter::setLength(double tempo, double division, double sampleRate) {
	// This math is definitely wrong lmao i'm so tired rn
	deckLength = tempo * division * sampleRate;
}

double Stutter::process(double input) {

	// Just return the input for now cause i dunno wut i'm doing
	return input;

	// Capture a new stutter deck
	for (int i = 0; i < deckLength; i++) {
		deck[i] = input;
		// return input as deck is being captured
	}

	// Once deck is full, push it to output and repeat
	for (int i = 0; i < deckLength; i++) {
		// Set output equal to stutter deck
		// How to synchronize looped deck with output?
		// How to return to beginning of stutter deck once it reaches the end?
	}
}
