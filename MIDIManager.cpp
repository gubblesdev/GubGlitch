#include "MIDIManager.h"


void MIDIManager::onMessage(IMidiMsg* midiMsg) {
	IMidiMsg::EStatusMsg status = midiMsg->StatusMsg();
	if (status == IMidiMsg::kNoteOn || status == IMidiMsg::kNoteOff) {
		// check if in specific range before adding??
		mQueue.Add(midiMsg);
	}
}

/*

	OKAY LETS FUCKIN FIGURE THIS SHIT OUT

	advance() just sets up variables for chopper and stutter
	have separate helper functions that return some number for each effect
	global variables that state whether each module is active 
	only do something if that return value has changed 
	(fuck what if you release and press down the same key quickly tho... prolly handle that from within the MIDI queue to ensure reset)
	create hasChanged boolean to ensure update is on single frame??

*/


void MIDIManager::advance() {
	
	// Call this to change param... fucking somehow??
	//SetParameterFromGUI(kChop_16th, 1.0);

	// if queue is empty, hasChanged = false
	// otherwise hasChanged = true

	while (!mQueue.Empty()) {
		IMidiMsg* midiMessage = mQueue.Peek();
		if (midiMessage->mOffset > mOffset) break;

		IMidiMsg::EStatusMsg status = midiMessage->StatusMsg();
		int note = midiMessage->NoteNumber();
		int velocity = midiMessage->Velocity();

		int stutLastNote;
		int chopLastNote;
		int keyLastNote;

		// Queue is filtered to only Note On/Off messages
		if (status == IMidiMsg::kNoteOn && velocity) {
			if (mKeyStatus[note] == false) {
				mKeyStatus[note] = true;
				mNumKeys += 1;
			}

			// Selective polyphony
			if (note >= 12 && note <= 23) {
				if (note != chopLastNote) {
					chopLastNote = note;
					// activate chopper
				}
			}

			else if (note >= 24) {
				if (note != keyLastNote) {
					keyLastNote = note;
					keyLastFreq = noteToFreq(keyLastNote);
					keyLastVel = velocity;
				}
			}

			else if (note <= 11) {
				if (note != stutLastNote) {
					stutLastNote = note;
					// activate stutter
				}
			}
		}

		// Note Off
		else {
			if (mKeyStatus[note]) {
				mKeyStatus[note] = false;
				mNumKeys -= 1;
			}

			// If the last note in each range was released, deactivate the associated effect
			if (note >= 12 && note <= 23) {
				if (note == chopLastNote) {
					chopLastNote = -1;
					// deactivate chopper
				}
			}
			else if (note <= 24) {
				if (note == keyLastNote) {
					keyLastNote = -1;
					keyLastFreq = -1.0;
					keyLastVel = 0;
				}
			}
			else if (note <= 11) {
				if (note == stutLastNote) {
					stutLastNote = -1;
					// Deactivate stutter
				}
			}
		}
		mQueue.Remove();
	}
	mOffset++;
}
