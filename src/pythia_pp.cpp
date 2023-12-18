#include "cstdlib"
#include <ctime>
#include <iostream>

#include "Pythia8/Pythia.h"
#include "Pythia8/Plugins.h"

#include "LHAPDF/LHAPDF.h"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/Selector.hh"

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
    const auto rootOutputFile = std::string (argv[4]);
    const auto iThread = strtol(argv[5], nullptr, 10);

    // Generator
    Pythia8::Pythia pythia;
    pythia.readFile(settingsFile);
    TFile outputTFile(rootOutputFile.c_str(), "RECREATE");

    Float_t px, py, pz, E, sigma_tot;
    // Particle iType conventions: 
    //  0 -- partons (initial from 2->2 process),
    //  1 -- hadrons, 
    //  2 -- jets (collected with FastJet)
    //  3 (and further) -- reserved for future
    // iColor and iFlavour are used for partons with standard Pythia conventions
    Int_t iType; //, iColor, iFlavour;
    Int_t Event_no; // Event number (WARNING: might be ambigious for multi-threading)
    // Set up output TTree
    TTree tr("part_jet", "part_jet");
    tr.Branch("px", &px);
    tr.Branch("py", &py);
    tr.Branch("pz", &pz);
    tr.Branch("E", &E);
    tr.Branch("type", &iType);
    tr.Branch("event_no", &Event_no);
    tr.Branch("sigma_tot", &sigma_tot);

    // Set up statistics histogram
    // Use 1st bin to store number of generated events
    TH1F stat_h("stat_h", "stat_h", 10, 0., 10.);

    // Initialize Pythia
    pythia.init();

    // Choose a jet definition
    const double R = 0.4;
    fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, R);

    const float rapidity_cut = 4.7;
    fastjet::Selector select_rapidity = fastjet::SelectorAbsRapMax(rapidity_cut);
    fastjet::Selector select_hard = fastjet::SelectorNHardest(2);  
    fastjet::Selector select_both = select_hard && select_rapidity; // only hardest dijets within acceptance

    unsigned int nAccepted = 0;
     // Begin event loop. Generate event; skip if generation aborted.
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) 
    {
        if (!pythia.next()) continue;
        nAccepted++;
        // Event ID
        Event_no = iEvent+nEvents*iThread; // Shift event number to avoid mixing when used in multiple threads

        // Access hard 2->2 process products
        auto hard_parton1 = pythia.event[5];
        auto hard_parton2 = pythia.event[6];
        if (fabs(hard_parton1.eta()) < rapidity_cut && fabs(hard_parton2.eta()) < rapidity_cut )
        {
            iType = 0;
            for(const auto& parton : {hard_parton1, hard_parton2})
            {
                px = parton.px();
                py = parton.py();
                pz = parton.pz();
                E = parton.e();
                tr.Fill();
            }
        }
            
        std::vector<fastjet::PseudoJet> hadrons;

        // Particle loop
        for (int i = 0; i < pythia.event.size(); ++i)
        {
            auto particle = pythia.event[i];

            if (particle.isHadron() && particle.isFinal())
                hadrons.push_back(fastjet::PseudoJet(particle.px(), particle.py(), particle.pz(), particle.e()));
        }
        fastjet::ClusterSequence cs(hadrons, jet_def);
        std::vector<fastjet::PseudoJet> jets = select_both(cs.inclusive_jets());
        for(const auto& jet : jets)
        {
            px = jet.px();
            py = jet.py();
            pz = jet.pz();
            E = jet.E();
            iType = 2;
            tr.Fill();
        }

        // Get cross-section over all processes (hopefully only hard 2->2)
        sigma_tot = pythia.info.sigmaGen();
    }
    tr.Write();
    stat_h.SetBinContent(1, nEvents);
    stat_h.SetBinContent(2, nAccepted);
    stat_h.SetBinContent(3, pythia.info.sigmaGen()); // mbarn
    stat_h.SetBinError(3, pythia.info.sigmaErr()); // error
    stat_h.Write();

    return 0;
}
