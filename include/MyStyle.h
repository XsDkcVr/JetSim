#pragma once

#include <TStyle.h>
#include <TROOT.h>
#include <TAxis.h>

class MyStyle
{
public:
    MyStyle()
    {
        styleName = "MyStyle";
        // Creating TStyle object
        style = new TStyle(styleName.c_str(), styleName.c_str());

        // Defining style parameters
        style->SetCanvasBorderMode(0);
        style->SetCanvasBorderSize(0);
        style->SetCanvasColor(0);
        style->SetPadLeftMargin(0.2);
        style->SetPadBottomMargin(0.2);
        style->SetOptStat(0);
        style->SetOptFit(0);
        style->SetErrorX(0);
        style->SetCanvasPreferGL(kTRUE);
        style->SetLegendBorderSize(0);
        style->SetLegendFillColor(0);
        style->SetLabelSize(0.05);
        style->SetLabelOffset(0.01);
        style->SetPadTickX(1);
        style->SetPadTickY(1);
        style->SetTitleXOffset(2.);
        style->SetTitleYOffset(2.);
        style->SetTitleSize(0.04, "xy");
        style->SetOptTitle(0);
        style->SetTitleAlign(22);
        
    }

    std::string GetStyleName() {return styleName;}
    ~MyStyle() {delete style;}

private:
    TStyle* style;
    std::string styleName;

};