#ifndef RunAction_hh
#define RunAction_hh

#include "Randomize.hh"
#include <iomanip>

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4Run.hh"

/* ROOT
#include "G4UnitsTable.hh"
#include <TFileMerger.h>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TSystem.h"
#include <thread>
#include "TROOT.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
using namespace ROOT;
*/

#include "3.0_DetectorConstruction.hh"
#include "5_PrimaryGenerator.hh"
#include "6.1_Run.hh"



class MyRunAction : public G4UserRunAction
{
    public:
        MyRunAction();
        ~MyRunAction();

        virtual void BeginOfRunAction(const G4Run *) override;
        virtual void EndOfRunAction(const G4Run *) override;

        G4Run * GenerateRun() override;
        
    private:
        Run * fRun = nullptr;
};

#endif