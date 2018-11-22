#ifndef __GUBGLITCH__
#define __GUBGLITCH__

#include "IPlug_include_in_plug_hdr.h"
#include "Oscillator.h"
#include "Stutter.h"

class GubGlitch : public IPlug
{
public:
  GubGlitch(IPlugInstanceInfo instanceInfo);
  ~GubGlitch();

  double gSampleRate;

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double* inputs[], double* outputs[], int nFrames);

private:
  Oscillator mOscillator;
  int chopperDivision;
  double gTempo;
  double gChopperMix = 1.0;
  Stutter gStutterL;
  Stutter gStutterR;
};

#endif
