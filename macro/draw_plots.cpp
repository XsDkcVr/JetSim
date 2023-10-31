#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1.h>
#include <TMath.h>
#include <TLegend.h>
#include <MyStyle.h>
#include <TROOT.h>

void draw_plots()
{
    MyStyle mystyle;
    gROOT->SetStyle(mystyle.GetStyleName().c_str());
    gROOT->ForceStyle();

    // gStyle->SetOptStat(0);
    // gStyle->SetErrorX(0);
    // gStyle->SetOptFit(0);
    // gStyle->SetPadTickX(1);
    // gStyle->SetPadTickY(1);
    // Disable ROOT ownership of histograms

    TH1::AddDirectory(kFALSE);

    std::unique_ptr<TFile> inFilePythia(TFile::Open("pythia_output.root", "READ"));
    std::unique_ptr<TFile> inFileLHAPDF(TFile::Open("lhapdf_output.root", "READ"));
    //std::unique_ptr<TH1D> CGhist(inFilePythia->Get<TH1D>("photon_TotalPrompt"));
    std::unique_ptr<TH1D> CGhistPythia(inFilePythia->Get<TH1D>("photon_1"));
    std::unique_ptr<TH1D> CGhistLHAPDF(inFileLHAPDF->Get<TH1D>("cross_section_px"));
    std::unique_ptr<TH1D> stats(inFilePythia->Get<TH1D>("runStatistics"));

    std::unique_ptr<TCanvas> can1(new TCanvas("can1", "", 600, 600));
    can1->cd();
    can1->SetLogy();
    can1->SetLogx();
    can1->SetBottomMargin(0.15);
    can1->SetLeftMargin(0.23);
    can1->SetRightMargin(0.1);

    auto xaxis = CGhistLHAPDF->GetXaxis();
    auto yaxis = CGhistLHAPDF->GetYaxis();

    for (auto& axis : {xaxis, yaxis})
    {
        axis->CenterTitle();
        axis->SetTitleSize(0.06);
        axis->SetTitleOffset(1.1);
        axis->SetLabelSize(0.05);

    }
    xaxis->SetTitle("p_{T} [GeV]");
    yaxis->SetTitle("E#kern[-0.6]{ }#frac{d^{3}#sigma}{d#kern[0.2]{p}^{3}}  [pb GeV^{-2}]");
    yaxis->SetTitleOffset(1.5);
    xaxis->SetRangeUser(3, 15);

    CGhistPythia->Scale(1/stats->GetBinContent(1));
    //CGhistPythia->Scale(stats->GetBinContent(2));  // Multiply by total gen cross-sec
    //CGhistPythia->Scale(1/42.2);  // Divide by total pp cross-sec
    CGhistPythia->Scale(1e+9); // to pb

    CGhistLHAPDF->Scale(1e+9); // to pb

    for (int i=0; i<CGhistPythia->GetNbinsX(); i++)
    {
        auto n = CGhistPythia->GetBinContent(i);
        auto pt = CGhistPythia->GetBinCenter(i);
        auto dpt = CGhistPythia->GetBinWidth(i);
        CGhistPythia->SetBinContent(i, n/(2*TMath::Pi()*pt*dpt));
        CGhistPythia->SetBinError(i, 0);
    }

    CGhistPythia->SetTitle("");
    CGhistPythia->SetMarkerStyle(20);
    CGhistPythia->SetMarkerSize(1);
    CGhistPythia->SetLineColor(kBlack);
    CGhistPythia->SetLineWidth(3);
    CGhistPythia->SetMarkerColor(kBlack);

    CGhistLHAPDF->SetLineWidth(3);
    CGhistLHAPDF->SetLineColor(kBlack);
    CGhistLHAPDF->SetLineStyle(9);
    CGhistLHAPDF->SetMarkerColor(kBlack);


    CGhistLHAPDF->Draw("hist c");
    CGhistPythia->Draw("hist c same");

    std::unique_ptr<TLegend> leg(new TLegend(0.44, 0.7, 0.94, 0.86));
    leg->SetTextSize(0.035);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(CGhistPythia.get(), "#bf{PYTHIA8.3, CT10NLO}", "l");
    leg->AddEntry(CGhistLHAPDF.get(), "#bf{LO calc., CT10nlo}", "l");
    leg->AddEntry(CGhistPythia.get(), "qg #rightarrow #gammaq", "");
    leg->AddEntry(CGhistPythia.get(), "p+p #sqrt{s} = 8 TeV", "");
    leg->AddEntry(CGhistPythia.get(), "|#eta| < 0.5", "");
    leg->Draw("SAME");

    can1->SaveAs("qgcompton.pdf");

}