#include<iostream>
#include<fstream>

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

void ROOT_2b(){
TFile signal("PsuedoData_Histogram_100fb.root");

//Creat Canvas
TCanvas *sig=new TCanvas()

//Create histograms
TH1D *sig;
TH1* invariant_mass=new TH1D("mass","invariant mass",100,0.0,200.0);

//Plot the psuedo data
signal.GetObject("signal",sig);
sig->Draw();

double event_weight,invariant_mass;
tree->
//loop the events
size_t nEntries=tree->GetEntries();
for(size_t i=0;i<nEntries;i++){
    tree->GetEntry(i);
    
}
}
