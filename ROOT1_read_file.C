#include<iostream>
#include<fstream>

#include<TFile.h>
#include<TTree.h>


void ROOT1_read_file(){
    TFile *file = TFile::Open("energy_data.root");

    TTree *measurements = nullptr;
    file->GetObject("Measurements",measurements);

    float cpu,powa;
    char timestamp[30];
    measurements->SetBranchAddress("cpu",&cpu);
    measurements->SetBranchAddress("powa",&powa);
    measurements->SetBranchAddress("timestamp",&timestamp);

    measurements->GetEntry(0);

    float minPow=powa;
    float maxPow=powa;
    float nPow=powa;
    float avePow=0.0;
    float totalE=0.0;

    Long64_t n=measurements->GetEntries();
    for(Long64_t i=0;i<n;i++){
        measurements->GetEntry(i);
        if (cpu>90.0){
            std::cout<<"Timestamp is "<<timestamp<<std::endl;
            std::cout<<"cpu: "<<cpu<<std::endl;
        }

        if(powa<minPow){
            minPow=powa;
        }
        if(powa>maxPow){
            maxPow=powa;
        }
        
        avePow=avePow+powa;
        if(i>0){
            totalE=totalE+(nPow+powa)*5.0;
            nPow=powa;
        }

    }
    avePow=avePow/n;
    totalE=totalE/2;
    std::cout<<"minimum power is: "<<minPow<<std::endl;
    std::cout<<"maxmum power is: "<<maxPow<<std::endl;
    std::cout<<"average power is: "<<avePow<<std::endl;
    std::cout<<"Total energy is: "<<totalE<<std::endl;

    file->Close();
    delete file;

}
