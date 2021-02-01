// PluginSimplexSynth.hpp
// Eric Sluyter (wondersluyter@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace SimplexSynth {

class SimplexSynth : public SCUnit {
public:
    SimplexSynth();

    // Destructor
    // ~SimplexSynth();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
    double phase;
    double sd;
};

} // namespace SimplexSynth
