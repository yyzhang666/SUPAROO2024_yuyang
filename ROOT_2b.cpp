#include<iostream>
#include<fstream>

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

void ROOT_2b(){
TFile *BG=TFile::Open("Background_1fb.root");

TH1D *hist_mass=new TH1D("mass","weighted invariant mass",100,0.0,200.0);

TTree *tree=nullptr;
BG->GetObject("tree",tree);

double w,m;

tree->SetBranchAddress("eventWeight",&w);
tree->SetBranchAddress("invariantMass",&m);

//loop the events
size_t nEntries=tree->GetEntries();
for(size_t i=0;i<nEntries;i++){
    tree->GetEntry(i);
    hist_mass->Fill(m,w);
}

TH1D *hist_mass2=(TH1D*)(hist_mass->Clone("hist_mass2"));
hist_mass2->Scale(100.0);
hist_mass2->Fit("gaus");

TCanvas *canvas=new TCanvas();
hist_mass2->Draw();
canvas->Update();

BG->Close();
}
