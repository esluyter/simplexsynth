// PluginSimplexSynth.cpp
// Eric Sluyter (wondersluyter@gmail.com)

#include "SC_PlugIn.hpp"
#include "SimplexSynth.hpp"
#include "SimplexNoise.h"

static InterfaceTable* ft;

namespace SimplexSynth {

SimplexSynth::SimplexSynth() {
    mCalcFunc = make_calc_function<SimplexSynth, &SimplexSynth::next>();
    next(1);
}

void SimplexSynth::next(int nSamples) {
    const float* x = in(0);
    const float* y = in(1);
    float oct = in0(2);
    float* outbuf = out(0);

    for (int i = 0; i < nSamples; ++i) {
      float xtemp = x[i];
      float ytemp = y[i];
      float weight = 1.0;
      outbuf[i] = SimplexNoise::noise(xtemp, ytemp);
      for (int n = 1; n < oct; ++n) {
        xtemp *= 2;
        ytemp *= 2;
        weight /= 2;
        outbuf[i] = outbuf[i] + (SimplexNoise::noise(xtemp, ytemp) * weight);
      }
    }

}

} // namespace SimplexSynth

PluginLoad(SimplexSynthUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SimplexSynth::SimplexSynth>(ft, "SimplexSynth");
}
