#include<iostream>
#include<fstream>

#include<nlohmann/json.hpp>
#include<TFile.h>
#include<TTree.h>

using json = nlohmann::json;

int main(){
    std::ifstream file("energy_data.json");
    json data;
    file>>data;

    TFile rootFile(energy_data.root,"RECREATE");
    TTree tree("Measurements");

    float cpu,frq,ram,powa,gpu;
    char timestamp[30];

    tree.Branch("cpu",&cpu);
    tree.Branch("frq",&frq);
    tree.Branch("ram", &ram);
    tree.Branch("powa", &powa);
    tree.Branch("gpu", &gpu);
    tree.Branch("timestamp",&timestamp);

    for (auto& entry : data["measurements"].items()) {
        timestamp = entry.key(); 
        cpu = entry.value()["cpu"];
        frq = entry.value()["frq"];
        ram = entry.value()["ram"];
        powa = entry.value()["powa"];
        gpu = entry.value()["gpu"];
        tree.Fill();
    }

    tree.Write();
    rootFile.Close();

    return 0;

}