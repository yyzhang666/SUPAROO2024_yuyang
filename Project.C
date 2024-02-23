#include<iostream>
#include<fstream>

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

void Project(){
TFile *mys = TFile::Open("mystery_nutple.root");

TTree *tree=nullptr;
mys->GetObject("Mystery",tree);
size_t nEntries=tree->GetEntries();
for(size_t i=0;i<nEntries;i++){
    tree->GetEntry(i);

}

TCanvas *canvas = new TCanvas("canvas","Signal data",800,600);
sig->Draw();
canvas->Update();

}