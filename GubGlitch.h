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

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double* inputs[], double* outputs[], int nFrames);

private:
  Oscillator mOscillator;
  int chopperDivision;
  double mTempo;
  double mChopperMix = 1.0;
  Stutter mStutterL;
  Stutter mStutterR;
};

#endif
