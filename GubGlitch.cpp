#include "GubGlitch.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

//Number of presets
const int kNumPrograms = 1;

enum EParams
{
  kChopperMix = 0,
  kChop_2nd = 1,
  kChop_4th = 2,
  kChop_8th = 3,
  kChop_16th = 4,
  kChop_32nd = 5,
  kChop_64th = 6,
  kChop_3rd = 7,
  kChop_6th = 8,
  kChop_12th = 9,
  kChop_24th = 10,
  kChop_48th = 11,
  kChop_hold = 12,

  kStut_2nd = 13,
  kStut_4th = 14,
  kStut_8th = 15,
  kStut_16th = 16,
  kStut_32nd = 17,
  kStut_64th = 18,
  kStut_3rd = 19,
  kStut_6th = 20,
  kStut_12th = 21,
  kStut_24th = 22,
  kStut_48th = 23,
  kStut_key = 24,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kChopperMixX = 669,
  kChopperMixY = 436,
  kChopperMixFrames = 128,

  kChop_2ndX = 109,
  kChop_2ndY = 347,

  kChop_4thX = 193,
  kChop_4thY = 347,

  kChop_8thX = 277,
  kChop_8thY = 347,

  kChop_16thX = 361,
  kChop_16thY = 347,

  kChop_32ndX = 445,
  kChop_32ndY = 347,

  kChop_64thX = 529,
  kChop_64thY = 347,

  kChop_3rdX = 151,
  kChop_3rdY = 263,

  kChop_6thX = 235,
  kChop_6thY = 263,

  kChop_12thX = 403,
  kChop_12thY = 263,

  kChop_24thX = 487,
  kChop_24thY = 263,

  kChop_48thX = 571,
  kChop_48thY = 263,

  kChop_holdX = 613,
  kChop_holdY = 347,

  kStut_2ndX = 109,
  kStut_2ndY = 115,

  kStut_4thX = 193,
  kStut_4thY = 115,

  kStut_8thX = 277,
  kStut_8thY = 115,

  kStut_16thX = 361,
  kStut_16thY = 115,

  kStut_32ndX = 445,
  kStut_32ndY = 115,

  kStut_64thX = 529,
  kStut_64thY = 115,

  kStut_3rdX = 151,
  kStut_3rdY = 31,

  kStut_6thX = 235,
  kStut_6thY = 31,

  kStut_12thX = 403,
  kStut_12thY = 31,

  kStut_24thX = 487,
  kStut_24thY = 31,

  kStut_48thX = 571,
  kStut_48thY = 31,

  kStut_keyX = 613,
  kStut_keyY = 115,
};

GubGlitch::GubGlitch(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
{
  TRACE;
  GetParam(kChopperMix)->InitDouble("Chopper Mix", 100.0, -100.0, 100.0, 1.0, "%");
  GetParam(kChop_2nd)->InitBool("Chopper 2nds", 0);
  GetParam(kChop_4th)->InitBool("Chopper 4ths", 0);
  GetParam(kChop_8th)->InitBool("Chopper 8ths", 0);
  GetParam(kChop_16th)->InitBool("Chopper 16ths", 0);
  GetParam(kChop_32nd)->InitBool("Chopper 32nds", 0);
  GetParam(kChop_64th)->InitBool("Chopper 64ths", 0);
  GetParam(kChop_3rd)->InitBool("Chopper 3rds", 0);
  GetParam(kChop_6th)->InitBool("Chopper 6ths", 0);
  GetParam(kChop_12th)->InitBool("Chopper 12ths", 0);
  GetParam(kChop_24th)->InitBool("Chopper 24ths", 0);
  GetParam(kChop_48th)->InitBool("Chopper 48ths", 0);
  GetParam(kChop_hold)->InitBool("Chopper Hold", 0);

  GetParam(kStut_2nd)->InitBool("Stutter 2nd", 0);
  GetParam(kStut_4th)->InitBool("Stutter 4th", 0);
  GetParam(kStut_8th)->InitBool("Stutter 8th", 0);
  GetParam(kStut_16th)->InitBool("Stutter 16th", 0);
  GetParam(kStut_32nd)->InitBool("Stutter 32nd", 0);
  GetParam(kStut_64th)->InitBool("Stutter 64th", 0);
  GetParam(kStut_3rd)->InitBool("Stutter 3rd", 0);
  GetParam(kStut_6th)->InitBool("Stutter 6th", 0);
  GetParam(kStut_12th)->InitBool("Stutter 12th", 0);
  GetParam(kStut_24th)->InitBool("Stutter 24th", 0);
  GetParam(kStut_48th)->InitBool("Stutter 48th", 0);

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);

  pGraphics->AttachBackground(BACKGROUND_ID, BACKGROUND_FN);
  IBitmap mixKnob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kChopperMixFrames);
  IBitmap cpad_2 = pGraphics->LoadIBitmap(CPAD_2_ID, CPAD_2_FN, 2);
  IBitmap cpad_4 = pGraphics->LoadIBitmap(CPAD_4_ID, CPAD_4_FN, 2);
  IBitmap cpad_8 = pGraphics->LoadIBitmap(CPAD_8_ID, CPAD_8_FN, 2);
  IBitmap cpad_16 = pGraphics->LoadIBitmap(CPAD_16_ID, CPAD_16_FN, 2);
  IBitmap cpad_32 = pGraphics->LoadIBitmap(CPAD_32_ID, CPAD_32_FN, 2);
  IBitmap cpad_64 = pGraphics->LoadIBitmap(CPAD_64_ID, CPAD_64_FN, 2);
  IBitmap cpad_3 = pGraphics->LoadIBitmap(CPAD_3_ID, CPAD_3_FN, 2);
  IBitmap cpad_6 = pGraphics->LoadIBitmap(CPAD_6_ID, CPAD_6_FN, 2);
  IBitmap cpad_12 = pGraphics->LoadIBitmap(CPAD_12_ID, CPAD_12_FN, 2);
  IBitmap cpad_24 = pGraphics->LoadIBitmap(CPAD_24_ID, CPAD_24_FN, 2);
  IBitmap cpad_48 = pGraphics->LoadIBitmap(CPAD_48_ID, CPAD_48_FN, 2);
  IBitmap cpad_hold = pGraphics->LoadIBitmap(CPAD_HOLD_ID, CPAD_HOLD_FN, 2);

  IBitmap spad_2 = pGraphics->LoadIBitmap(SPAD_2_ID, SPAD_2_FN, 2);
  IBitmap spad_4 = pGraphics->LoadIBitmap(SPAD_4_ID, SPAD_4_FN, 2);
  IBitmap spad_8 = pGraphics->LoadIBitmap(SPAD_8_ID, SPAD_8_FN, 2);
  IBitmap spad_16 = pGraphics->LoadIBitmap(SPAD_16_ID, SPAD_16_FN, 2);
  IBitmap spad_32 = pGraphics->LoadIBitmap(SPAD_32_ID, SPAD_32_FN, 2);
  IBitmap spad_64 = pGraphics->LoadIBitmap(SPAD_64_ID, SPAD_64_FN, 2);
  IBitmap spad_3 = pGraphics->LoadIBitmap(SPAD_3_ID, SPAD_3_FN, 2);
  IBitmap spad_6 = pGraphics->LoadIBitmap(SPAD_6_ID, SPAD_6_FN, 2);
  IBitmap spad_12 = pGraphics->LoadIBitmap(SPAD_12_ID, SPAD_12_FN, 2);
  IBitmap spad_24 = pGraphics->LoadIBitmap(SPAD_24_ID, SPAD_24_FN, 2);
  IBitmap spad_48 = pGraphics->LoadIBitmap(SPAD_48_ID, SPAD_48_FN, 2);
  IBitmap spad_key = pGraphics->LoadIBitmap(SPAD_KEY_ID, SPAD_KEY_FN, 2);

  pGraphics->AttachControl(new IKnobMultiControl(this, kChopperMixX, kChopperMixY, kChopperMix, &mixKnob));
  pGraphics->AttachControl(new IContactControl(this, kChop_2ndX, kChop_2ndY, kChop_2nd, &cpad_2));
  pGraphics->AttachControl(new IContactControl(this, kChop_4thX, kChop_4thY, kChop_4th, &cpad_4));			// TO DO: MIDI integration uugghhhh
  pGraphics->AttachControl(new IContactControl(this, kChop_8thX, kChop_8thY, kChop_8th, &cpad_8));
  pGraphics->AttachControl(new IContactControl(this, kChop_16thX, kChop_16thY, kChop_16th, &cpad_16));
  pGraphics->AttachControl(new IContactControl(this, kChop_32ndX, kChop_32ndY, kChop_32nd, &cpad_32));
  pGraphics->AttachControl(new IContactControl(this, kChop_64thX, kChop_64thY, kChop_64th, &cpad_64));
  pGraphics->AttachControl(new IContactControl(this, kChop_3rdX, kChop_3rdY, kChop_3rd, &cpad_3));
  pGraphics->AttachControl(new IContactControl(this, kChop_6thX, kChop_6thY, kChop_6th, &cpad_6));
  pGraphics->AttachControl(new IContactControl(this, kChop_12thX, kChop_12thY, kChop_12th, &cpad_12));
  pGraphics->AttachControl(new IContactControl(this, kChop_24thX, kChop_24thY, kChop_24th, &cpad_24));
  pGraphics->AttachControl(new IContactControl(this, kChop_48thX, kChop_48thY, kChop_48th, &cpad_48));
  pGraphics->AttachControl(new IContactControl(this, kChop_holdX, kChop_holdY, kChop_hold, &cpad_hold));

  pGraphics->AttachControl(new IContactControl(this, kStut_2ndX, kStut_2ndY, kStut_2nd, &spad_2));
  pGraphics->AttachControl(new IContactControl(this, kStut_4thX, kStut_4thY, kStut_4th, &spad_4));
  pGraphics->AttachControl(new IContactControl(this, kStut_8thX, kStut_8thY, kStut_8th, &spad_8));
  pGraphics->AttachControl(new IContactControl(this, kStut_16thX, kStut_16thY, kStut_16th, &spad_16));
  pGraphics->AttachControl(new IContactControl(this, kStut_32ndX, kStut_32ndY, kStut_32nd, &spad_32));
  pGraphics->AttachControl(new IContactControl(this, kStut_64thX, kStut_64thY, kStut_64th, &spad_64));
  pGraphics->AttachControl(new IContactControl(this, kStut_3rdX, kStut_3rdY, kStut_3rd, &spad_3));
  pGraphics->AttachControl(new IContactControl(this, kStut_6thX, kStut_6thY, kStut_6th, &spad_6));
  pGraphics->AttachControl(new IContactControl(this, kStut_12thX, kStut_12thY, kStut_12th, &spad_12));
  pGraphics->AttachControl(new IContactControl(this, kStut_24thX, kStut_24thY, kStut_24th, &spad_24));
  pGraphics->AttachControl(new IContactControl(this, kStut_48thX, kStut_48thY, kStut_48th, &spad_48));
  pGraphics->AttachControl(new IContactControl(this, kStut_keyX, kStut_keyY, kStut_key, &spad_key));

  AttachGraphics(pGraphics);
}

GubGlitch::~GubGlitch() {}

void GubGlitch::ProcessDoubleReplacing(double* inputs[], double* outputs[], int nFrames)
{
  mTempo = this->GetTempo();
  double* inL = inputs[0];
  double* inR = inputs[1];
  double* outL = outputs[0];
  double* outR = outputs[1];

  for (int s = 0; s < nFrames; ++s)
  {

	  if (mStutterL.isActive) {
		  outL[s] = mStutterL.process(inL[s]) * mOscillator.nextSample(mTempo, mChopperMix);
		  outR[s] = mStutterR.process(inR[s]) * mOscillator.nextSample(mTempo, mChopperMix);
	   }
	  else {
		  outL[s] = inL[s] * mOscillator.nextSample(mTempo, mChopperMix);
		  outR[s] = inR[s] * mOscillator.nextSample(mTempo, mChopperMix);
	  }
  }
}

void GubGlitch::Reset()
{
  TRACE;
  IMutexLock lock(this);
  mOscillator.setSampleRate(GetSampleRate());
}

// TO DO: Modify these godawful parameters into something clean and readable

void GubGlitch::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  switch (paramIdx)
  {
  case kChop_2nd:
	  if (GetParam(kChop_2nd)->Value()) mOscillator.setChopper(2.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_4th:
	  if (GetParam(kChop_4th)->Value()) mOscillator.setChopper(4.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_8th:
	  if (GetParam(kChop_8th)->Value()) mOscillator.setChopper(8.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_16th:
	  if (GetParam(kChop_16th)->Value()) mOscillator.setChopper(16.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_32nd:
	  if (GetParam(kChop_32nd)->Value()) mOscillator.setChopper(32.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_64th:
	  if (GetParam(kChop_64th)->Value()) mOscillator.setChopper(64.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_3rd:
	  if (GetParam(kChop_3rd)->Value()) mOscillator.setChopper(3.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_6th:
	  if (GetParam(kChop_6th)->Value()) mOscillator.setChopper(6.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_12th:
	  if (GetParam(kChop_12th)->Value()) mOscillator.setChopper(12.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_24th:
	  if (GetParam(kChop_24th)->Value()) mOscillator.setChopper(24.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_48th:
	  if (GetParam(kChop_48th)->Value()) mOscillator.setChopper(48.0);
	  else mOscillator.setActive(false);
	  break;

  case kChop_hold:
	  if (GetParam(kChop_hold)->Value()) mOscillator.setHold(true);
	  else mOscillator.setHold(false);
	  break;

  case kChopperMix:
	  // call function to change mix values; pass in parameter value
	  mChopperMix = GetParam(kChopperMix)->Value();
	  mOscillator.updateMix(mChopperMix);
	  break;

  case kStut_2nd:
	  if (GetParam(kStut_2nd)->Value()) {
		  mStutterL.setLength(mTempo, 2.0, mSampleRate);
		  mStutterR.setLength(mTempo, 2.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

  case kStut_4th:
	  if (GetParam(kStut_4th)->Value()) {
		  mStutterL.setLength(mTempo, 4.0, mSampleRate);
		  mStutterR.setLength(mTempo, 4.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

  case kStut_8th:
	  if (GetParam(kStut_8th)->Value()) {
		  mStutterL.setLength(mTempo, 8.0, mSampleRate);
		  mStutterR.setLength(mTempo, 8.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

  case kStut_16th:
	  if (GetParam(kStut_16th)->Value()) {
		  mStutterL.setLength(mTempo, 16.0, mSampleRate);
		  mStutterR.setLength(mTempo, 16.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

  case kStut_32nd:
	  if (GetParam(kStut_32nd)->Value()) {
		  mStutterL.setLength(mTempo, 32.0, mSampleRate);
		  mStutterR.setLength(mTempo, 32.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

  case kStut_64th:
	  if (GetParam(kStut_64th)->Value()) {
		  mStutterL.setLength(mTempo, 64.0, mSampleRate);
		  mStutterR.setLength(mTempo, 64.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

  case kStut_3rd:
	  if (GetParam(kStut_3rd)->Value()) {
		  mStutterL.setLength(mTempo, 3.0, mSampleRate);
		  mStutterR.setLength(mTempo, 3.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

  case kStut_6th:
	  if (GetParam(kStut_6th)->Value()) {
		  mStutterL.setLength(mTempo, 6.0, mSampleRate);
		  mStutterR.setLength(mTempo, 6.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

  case kStut_12th:
	  if (GetParam(kStut_12th)->Value()) {
		  mStutterL.setLength(mTempo, 12.0, mSampleRate);
		  mStutterR.setLength(mTempo, 12.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

  case kStut_24th:
	  if (GetParam(kStut_24th)->Value()) {
		  mStutterL.setLength(mTempo, 24.0, mSampleRate);
		  mStutterR.setLength(mTempo, 24.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

  case kStut_48th:
	  if (GetParam(kStut_48th)->Value()) {
		  mStutterL.setLength(mTempo, 48.0, mSampleRate);
		  mStutterR.setLength(mTempo, 48.0, mSampleRate);
	  }
	  else {
		  mStutterL.setActive(false);
		  mStutterR.setActive(false);
	  }
	  break;

    default:
      break;
  }
}
