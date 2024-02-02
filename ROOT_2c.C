#include<iostream>
#include<fstream>

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

void ROOT_2c(){
//Open files
TFile *signal = TFile::Open("PseudoData_Histogram_100fb.root");
TFile *BG=TFile::Open("Background_1fb.root");

//Book histograms
TH1D *sig=nullptr;
TH1D *hist_mass=new TH1D("mass","weighted invariant mass",100,0.0,200.0);

//Get histogram from the data
signal->GetObject("signal",sig);

//Get histogram from the background as task 2b
TTree *tree=nullptr;
BG->GetObject("tree",tree);

double w,m;

tree->SetBranchAddress("eventWeight",&w);
tree->SetBranchAddress("invariantMass",&m);

size_t nEntries=tree->GetEntries();
for(size_t i=0;i<nEntries;i++){
    tree->GetEntry(i);
    hist_mass->Fill(m,w);
}

TH1D *hist_mass2=(TH1D*)(hist_mass->Clone("hist_mass2"));
hist_mass2->Scale(100.0);

//Draw the data and background on the same plot
TCanvas *canvas = new TCanvas("canvas","Signal data",800,600);

TPad *pad1 = new TPad("pad1","Signal and Background", 0, 0.3, 1, 1.0);
pad1->Draw();
pad1->cd();
sig->Draw();
hist_mass2->Draw("SAME");
canvas->Update();

//Create a Pad to draw the difference
canvas->cd();
TPad *pad2 = new TPad("pad2","Difference", 0, 0.3, 1, 1.0);
pad2->Draw();
pad2->cd();

auto rp = new TRatioPlot(sig,hist_mass2);
rp->Draw();
canvas->Update();

}
