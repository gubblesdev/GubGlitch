#ifndef __GUBGLITCH__
#define __GUBGLITCH__

#include "IPlug_include_in_plug_hdr.h"
//#include "IGraphics.h"
//#include "IPlugBase.h"
#include "Chopper.h"
#include "Stutter.h"
#include "MIDIManager.h"

// Sample rate and tempo are GLOBALS
extern double gSampleRate;
extern double gTempo;

class GubGlitch : public IPlug
{
public:
  GubGlitch(IPlugInstanceInfo instanceInfo);
  ~GubGlitch();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double* inputs[], double* outputs[], int nFrames);

  void activateChopper(int div);
  void activateStutterDiv(int div);
  void activateStutterKey(double freq);
  void deactivateChopper();
  void deactivateStutter();

private:
  Chopper chopper;
  int chopperDivision;
  double chopperMix = 1.0;
  Stutter stutterL;
  Stutter stutterR;
  MIDIManager mMIDI;
};

#endif
