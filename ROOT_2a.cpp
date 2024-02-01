#include<iostream>
#include<fstream>

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"

void ROOT_2a(){
TFile signal("PsuedoData_Histogram_100fb.root");

//Creat Canvas
TCanvas *sig=new TCanvas()

//Plot the psuedo data
signal.GetObject("signal",sig);
sig->Draw();