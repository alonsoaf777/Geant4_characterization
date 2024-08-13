#include "RunAction.hh"

// EM13 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
#include "DetectorConstruction.hh"
#include "PrimaryGenerator.hh"
#include "Run.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include <iomanip>

MyRunAction::MyRunAction(MyDetectorConstruction * det, MyPrimaryGenerator * kin):fDetector(det), fPrimary(kin)
{
    G4AnalysisManager * analysisManager = G4AnalysisManager::Instance();
    
    analysisManager -> CreateNtuple("Photons", "Photons");
    analysisManager -> CreateNtupleIColumn("Event_Count");
    analysisManager -> CreateNtupleDColumn("X_axis");
    analysisManager -> CreateNtupleDColumn("Y_axis");
    analysisManager -> CreateNtupleDColumn("Z_axis");
    analysisManager -> CreateNtupleDColumn("Photons'_Wavelengths");
    analysisManager -> FinishNtuple(0);
    
    analysisManager -> CreateNtuple("Hits", "Hits");
    analysisManager -> CreateNtupleIColumn("Event_Count");
    analysisManager -> CreateNtupleDColumn("X_Detectors");
    analysisManager -> CreateNtupleDColumn("Y_Detectors");
    analysisManager -> CreateNtupleDColumn("Z_Detectors");
    analysisManager -> FinishNtuple(1);

    analysisManager -> CreateNtuple("Scoring", "Scoring");
    analysisManager -> CreateNtupleDColumn("Energy_Deposition");
    analysisManager -> FinishNtuple(2);
}

MyRunAction::~MyRunAction(){}

void MyRunAction::BeginOfRunAction(const G4Run * run)
{
    G4AnalysisManager * analysisManager = G4AnalysisManager::Instance();
    
    G4int runID = run -> GetRunID();
    std::stringstream strRunID;
    strRunID << runID;
    analysisManager -> OpenFile("Output" + strRunID.str() + ".root");

    // EM13 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
    // show Rndm status
    // if (isMaster) G4Random::showEngineStatus();

    // keep run condition
    if ( fPrimary ) 
    { 
        G4ParticleDefinition * particle = fPrimary -> GetParticleGun() -> GetParticleDefinition();
        G4double energy = fPrimary -> GetParticleGun() -> GetParticleEnergy();
        fRun -> SetPrimary(particle, energy);
    }
}

// EM13 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
G4Run * MyRunAction::GenerateRun()
{ 
    fRun = new Run(fDetector); 
    return fRun;
}

void MyRunAction::EndOfRunAction(const G4Run *)
{
    G4AnalysisManager * analysisManager = G4AnalysisManager::Instance();
    analysisManager -> Write();
    analysisManager -> CloseFile();

    // EM13 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
    // compute and print statistic 
    if (isMaster) fRun -> EndOfRun();
    // show Rndm status
    // if (isMaster) G4Random::showEngineStatus(); 
}