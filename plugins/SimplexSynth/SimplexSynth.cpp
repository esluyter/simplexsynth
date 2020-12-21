// PluginSimplexSynth.cpp
// Eric Sluyter (wondersluyter@gmail.com)

#include "SC_PlugIn.hpp"
#include "SimplexSynth.hpp"

static InterfaceTable* ft;

namespace SimplexSynth {

SimplexSynth::SimplexSynth() {
    mCalcFunc = make_calc_function<SimplexSynth, &SimplexSynth::next>();
    next(1);
}

void SimplexSynth::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(0);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace SimplexSynth

PluginLoad(SimplexSynthUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SimplexSynth::SimplexSynth>(ft, "SimplexSynth");
}
