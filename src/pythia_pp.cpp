// main54.cc is a part of the PYTHIA event generator.
// Copyright (C) 2023 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Authors: Juan Rojo <authors@pythia.org>.

// Keywords: parton distribution; LHAPDF;

// This program compares the internal and LHAPDF implementations of the
// NNPDF 2.3 QCD+QED sets, for results and for timing.
// Warning: this example is constructed to work for LHAPDF5.
// There seem to be differences when instead comparing with LHAPDF6.
#include "cstdlib"
#include <ctime>
#include <iostream>

#include "Pythia8/Pythia.h"
#include "Pythia8/PythiaParallel.h"

#include "LHAPDF/LHAPDF.h"
#include <random>

#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TROOT.h>

int main(int argc, char *argv[])
{
    const auto nEvents = strtol(argv[1], nullptr, 10);
    const auto seed = std::string(argv[2]);
    const auto settingsFile = std::string (argv[3]);

    const unsigned int NBINS = 20;
    const float PTMIN = 0.;
    const float PTMAX = 20.;

    // Generator.
    Pythia8 pythia;
    pythia.readFile(settingsFile);
    //pythia.readString("Random:setSeed = on");
    //pythia.readString("Random:Seed = " + seed);
    //pythia.readString("Parallelism:numThreads = 4");
    pythia.init();
    TTree tr;
    return 0;
}
