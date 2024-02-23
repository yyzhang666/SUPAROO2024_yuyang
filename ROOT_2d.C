#include<iostream>
#include<fstream>

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TTree.h"
#include "TRatioPlot.h"

void ROOT_2c(){
//Open files
TFile *signal = TFile::Open("PsuedoData_Histogram_100fb.root");
TFile *BG=TFile::Open("Background_1fb.root");
TFile *MC_signal=TFile::Open("Signal_1fb.root");

//Book histograms
TH1D *sig=nullptr;
TH1D *hist_mass=new TH1D("mass","weighted invariant mass",100,0.0,200.0);

//Get histogram from the data
signal->GetObject("signal",sig);

//Get histogram from the background and signal as task 2b
TTree *tree=nullptr;
TTree *tree2=nullptr;
BG->GetObject("tree",tree);
MC_signal->GetObject("tree",tree2);

double w1,m1,w2,m2;

tree->SetBranchAddress("eventWeight",&w1);
tree->SetBranchAddress("invariantMass",&m1);

tree2->SetBranchAddress("eventWeight",&w2);
tree2->SetBranchAddress("invariantMass",&m2);

size_t nEntries=tree->GetEntries();
size_t nEntries2=tree2->GetEntries();

//loop the background
for(size_t i=0;i<nEntries;i++){
    tree->GetEntry(i);
    hist_mass->Fill(m1,w1);
}

//loop the signal
for(size_t i=0;i<nEntries2;i++){
    tree2->GetEntry(i);
    hist_mass->Fill(m2,w2);
}

// Scale the histogram
TH1D *hist_mass2=(TH1D*)(hist_mass->Clone("hist_mass2"));

hist_mass2->Scale(100.0);

//Draw the data and background on the same plot
TCanvas *canvas = new TCanvas("canvas","Psuedo Signal data",800,600);

TPad *pad1 = new TPad("pad1","MC Signal and Background", 0, 0.2, 1.0, 1.0);
pad1->Draw();
pad1->cd();
sig->SetLineColor(kBlue);
sig->Draw();
hist_mass2->SetLineColor(kRed);
hist_mass2->Draw("SAME");
canvas->Update();

//Create a Pad to draw the difference
canvas->cd();
TPad *pad2 = new TPad("pad2","Difference", 0, 0.0, 1.0, 0.2);
pad2->Draw();
pad2->cd();

auto rp = new TRatioPlot(sig,hist_mass2);
rp->Draw();
canvas->Update();

}