#pragma once
#include <TH2D.h>
#include "LHAPDF/LHAPDF.h"


void dsigmadptdy_QCDCompton(double s, double alpha, const LHAPDF::PDF *pdf, const std::vector<int> quark_pids, TH2D *outputHist);