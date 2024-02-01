#include<iostream>
#include<fstream>

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

void ROOT_2a(){
TFile *signal = TFile::Open("PsuedoData_Histogram_100fb.root");
TH1D *sig;

signal->GetObject("signal",sig);

TCanvas *canvas = new TCanvas("canvas","Signal data",800,600);
sig->Draw();

signal->Close();
delete signal;

}