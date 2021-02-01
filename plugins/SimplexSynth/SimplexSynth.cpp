// PluginSimplexSynth.cpp
// Eric Sluyter (wondersluyter@gmail.com)

#include "SC_PlugIn.hpp"
#include "SimplexSynth.hpp"
#include "SimplexNoise.h"
#include <cmath>
#include "math.h"

static InterfaceTable* ft;

namespace SimplexSynth {

SimplexSynth::SimplexSynth() {
  this->phase = in0(6);
  this->sd = double(1.0) / this->sampleRate();
  mCalcFunc = make_calc_function<SimplexSynth, &SimplexSynth::next>();
  next(1);
}

void SimplexSynth::next(int nSamples) {
  double freq = in0(0);
  double incr = this->sd * freq * twopi;
  double offsetX = in0(1);
  double offsetY = in0(2);
  double radius = in0(3);
  float oct = in0(4);
  const float* syncSig = in(5);
  float iphase = in0(6);
  float* outbuf = out(0);

  for (int i = 0; i < nSamples; ++i) {
    this->phase = std::fmod(this->phase, twopi);
    double xtemp = cos(this->phase) * radius + offsetX;
    double ytemp = sin(this->phase) * radius + offsetY;
    float weight = 1.0;
    outbuf[i] = SimplexNoise::noise(xtemp, ytemp);
    for (int n = 1; n < oct; ++n) {
      xtemp *= 2;
      ytemp *= 2;
      weight /= 2;
      outbuf[i] = outbuf[i] + (SimplexNoise::noise(xtemp, ytemp) * weight);
    }
    this->phase += incr;
  }

}

} // namespace SimplexSynth

PluginLoad(SimplexSynthUGens) {
  // Plugin magic
  ft = inTable;
  registerUnit<SimplexSynth::SimplexSynth>(ft, "SimplexSynth");
}
