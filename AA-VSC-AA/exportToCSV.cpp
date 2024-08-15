#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

void exportRootToCSV(const char* rootFileName, const char* treeName, const char* branchName, const char* csvFileName) {
    TFile *file = TFile::Open(rootFileName);
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening ROOT file." << std::endl;
        return;
    }

    TTree *tree = (TTree*)file->Get(treeName);
    if (!tree) {
        std::cerr << "Error getting TTree." << std::endl;
        return;
    }

    std::ofstream csvFile(csvFileName);
    if (!csvFile.is_open()) {
        std::cerr << "Error opening CSV file." << std::endl;
        return;
    }

    csvFile << "Value" << std::endl;

    TBranch *branch = tree->GetBranch(branchName);
    if (!branch) {
        std::cerr << "Error getting branch." << std::endl;
        return;
    }

    Float_t value;
    branch->SetAddress(&value);

    for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
        tree->GetEntry(i);
        csvFile << value << std::endl;
    }

    file->Close();
    csvFile.close();
}
