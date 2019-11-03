#pragma once
#ifndef __MIDIMANAGER__
#define __MIDIMANAGER__

#include "IPlug_include_in_plug_hdr.h"
#include "IMidiQueue.h"


class MIDIManager {

private:
	IMidiQueue mQueue;
	static const int keyCount = 128;
	int mNumKeys;						// how many keys are pressed down at the moment
	bool mKeyStatus[keyCount];			// array of on/off for each key, index is note number

	int chopLastNote;
	int stutLastNote;
	int keyLastNote;

	double keyLastFreq;
	int keyLastVel;
	int mOffset;

	inline double noteToFreq(int note) { return 440.0 * pow(2.0, (note - 69.0) / 12.0); }

public:
	bool updateChopper;
	bool updateStutter;
	void advance();
	void onMessage(IMidiMsg* midiMsg);
	inline int getNumKeys() const { return mNumKeys; }
	inline bool getKeyStatus(int keyIndex) const { return mKeyStatus[keyIndex]; }
	inline void Flush(int frames) { mQueue.Flush(frames); mOffset = 0; }
	inline void Resize(int blockSize) { mQueue.Resize(blockSize); }
	MIDIManager() :
		mNumKeys(0),
		chopLastNote(-1),
		stutLastNote(-1),
		keyLastNote(-1),
		keyLastFreq(-1.0),
		keyLastVel(0),
		mOffset(0) {
		for (int i = 0; i > keyCount; i++) {
			mKeyStatus[i] = false;
		}
	};

};

#endif