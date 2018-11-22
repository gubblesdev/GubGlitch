#include "Stutter.h"
#include "IPlug/IPlug_include_in_plug_hdr.h"


void Stutter::setLength(double tempo, double division, double sampleRate) {
	// Calculate how many samples long the deck should be
	// Integer division truncates remainder; determine whether or not this is desirable behavior
	deckLength = ((60.0 / tempo) * (4.0 / division)) * sampleRate;
	deck.resize(deckLength);
	c = 0;
	isFull = false;
	isActive = true;
	weightA = sLength;
	weightB = 0;
}

double Stutter::process(double input) {

	// Fill the stutter deck until it's full
	if (!isFull) {
		// Average last values of the deck towards first value
		// Prevents pops and clicks when looping the deck
		if (c > deckLength - sLength) {
			deck[c++] = ((input * weightA) + (deck[0] * weightB)) / sLength;
			weightA--;
			weightB = sLength - weightA;
		}
		else
			deck[c++] = input;

		// Deck full, stop filling it
		if (c == deckLength)
			isFull = true;

		return input;
	}
	// Loop the deck after it's been filled
	else {
		if (c == deckLength)
			c = 0;
		return deck[c++];
	}
}
