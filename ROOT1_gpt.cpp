#include <fstream>
#include <nlohmann/json.hpp>
#include <TFile.h>
#include <TTree.h>

using json = nlohmann::json;

int main() {
    // 打开并读取JSON文件
    std::ifstream file("data.json");
    json data;
    file >> data;

    // 创建ROOT文件
    TFile rootFile("output.root", "RECREATE");
    TTree tree("Measurements", "Sensor Data");

    // 定义用于存储数据的变量
    float cpu, frq, ram, powa;
    int gpu;
    
    // 创建分支
    tree.Branch("cpu", &cpu, "cpu/F");
    tree.Branch("frq", &frq, "frq/F");
    tree.Branch("ram", &ram, "ram/F");
    tree.Branch("powa", &powa, "powa/F");
    tree.Branch("gpu", &gpu, "gpu/I");

    // 解析并填充数据
    for (auto& entry : data["measurements"].items()) {
        cpu = entry.value()["cpu"];
        frq = entry.value()["frq"];
        ram = entry.value()["ram"];
        powa = entry.value()["powa"];
        gpu = entry.value()["gpu"];
        tree.Fill();
    }

    // 写入并关闭ROOT文件
    tree.Write();
    rootFile.Close();

    return 0;
}
