#include "Stutter.h"
#include "IPlug/IPlug_include_in_plug_hdr.h"


void Stutter::setLength(double division) {
	// Calculate how many samples long the deck should be
	// Integer division truncates remainder; determine whether or not this is desirable behavior
	deckLength = ((60.0 / gTempo) * (4.0 / division)) * gSampleRate;
	deck.resize(deckLength);
	c = 0;
	isFull = false;
	isActive = true;
	weightA = lerpLength;
	weightB = 0;
}

void Stutter::setKeyLength(double freq) {
	deckLength = freq * gSampleRate;
	deck.resize(deckLength);
	c = 0;
	isFull = false;
	isActive = true;
	weightA = lerpLength;
	weightB = 0;
}

double Stutter::process(double input) {

	// Fill the stutter deck until it's full
	if (!isFull) {

		double output;
		deck[c++] = input;

		// To prevent pops and clicks when looping the deck, average last values of the deck towards first value
		// Done without writing to the deck itself to accomodate for variable length of KEY
		if (c > deckLength - lerpLength) {
			output = ((deck[c-1] * weightA) + (deck[0] * weightB)) / lerpLength;
			weightA--;
			weightB = lerpLength - weightA;
		}
		else output = input;

		// Deck full, stop filling it
		if (c == deckLength) {
			isFull = true;
			weightA = lerpLength;
			weightB = 0;
		}

		return output;
	}

	// Loop the deck after it's been filled
	else {

		if (c == deckLength) {
			c = 0;
			weightA = lerpLength;
			weightB = 0;
		}

		// To prevent pops and clicks when looping the deck, average last values of the deck towards first value 
		// Processed in realtime to accomodate for variable loop length with KEY
		if (c > deckLength - lerpLength) {
			double output = ((deck[c++] * weightA) + (deck[0] * weightB)) / lerpLength;
			weightA--;
			weightB = lerpLength - weightA;
			return output;
		}
		else return deck[c++];
	}
}
