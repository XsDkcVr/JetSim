#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1.h>
#include <TMath.h>
#include <TLegend.h>
#include <TROOT.h>
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RDFHelpers.hxx>
#include <ROOT/RDF/Utils.hxx>

#include "../include/MyStyle.h"


__attribute__ ((__unused__)) void draw_plots()
{
    MyStyle mystyle;
    gROOT->SetStyle(mystyle.GetStyleName().c_str());
    gROOT->ForceStyle();

    // Disable ROOT ownership of histograms
    //TH1::AddDirectory(kFALSE);
    ROOT::EnableImplicitMT(); 
    ROOT::RDataFrame pythia_dat("part_jet", "rootfiles/output_tree.root");
    //ROOT::RDF::Experimental::AddProgressBar(pythia_dat);


    const int can_width = 600;
    const int can_height = 600;
    std::unique_ptr<TCanvas> can1(new TCanvas("can1", "", can_width, can_height));
    can1->cd();
    can1->SetLogy();
    //can1->SetLogx();
    can1->SetBottomMargin(0.2);
    can1->SetLeftMargin(0.20);
    can1->SetRightMargin(0.1);

    auto test_hist = pythia_dat.Define("pt", [](float px, float py) {return sqrt(px*px+py*py);}, {"px", "py"})
                                .Filter([](float pt){return pt>5.0;}, {"pt"})
                                .Filter([](int type){return type == 2;},{"type"})
                                .Histo1D({"pt_dist", "pt_dist;p_{T} [GeV];Yield", 100, 0., 100.}, "pt");
    //auto test_hist = pythia_dat.Histo1D({"px", "pt_dist", 30, 0., 20.});
    test_hist->SetMarkerStyle(kCircle);
    test_hist->SetMarkerColor(kBlack);
    test_hist->SetMarkerSize(can_height*can_width*2e-6);
    test_hist->GetXaxis()->CenterTitle();
    test_hist->GetYaxis()->CenterTitle();
    
    test_hist->Draw("e1");

    //yaxis->SetTitle("E#kern[-0.6]{ }#frac{d^{3}#sigma}{d#kern[0.2]{p}^{3}}  [pb GeV^{-2}]");


    can1->SaveAs("plots/plot1.pdf");

}