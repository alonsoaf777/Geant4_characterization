#include "Randomize.hh"
#include <iomanip>

#include "G4Run.hh"
#include "G4UnitsTable.hh"

#include "3.0_DetectorConstruction.hh"
#include "5_PrimaryGenerator.hh"
#include "6.0_RunAction.hh"
#include "6.1_Run.hh"

MyRunAction::MyRunAction()
{
    G4AnalysisManager * analysisManager = G4AnalysisManager::Instance();
    
    // analysisManager -> CreateNtuple("Photons", "Photons");
    // analysisManager -> CreateNtupleIColumn("Event_Count");
    // analysisManager -> CreateNtupleDColumn("X_axis");
    // analysisManager -> CreateNtupleDColumn("Y_axis");
    // analysisManager -> CreateNtupleDColumn("Z_axis");
    // analysisManager -> CreateNtupleDColumn("Photons'_Wavelengths");
    // analysisManager -> FinishNtuple(0);
    
    // analysisManager -> CreateNtuple("Hits", "Hits");
    // analysisManager -> CreateNtupleIColumn("Event_Count");
    // analysisManager -> CreateNtupleDColumn("X_Detectors");
    // analysisManager -> CreateNtupleDColumn("Y_Detectors");
    // analysisManager -> CreateNtupleDColumn("Z_Detectors");
    // analysisManager -> FinishNtuple(1);

    // analysisManager -> CreateNtuple("Scoring", "Scoring");
    // analysisManager -> CreateNtupleDColumn("Energy_Deposition");
    // analysisManager -> FinishNtuple(2);

    analysisManager -> CreateNtuple("Transportation", "Transportation");
    analysisManager -> CreateNtupleDColumn("Mass_Atenuation");
    analysisManager -> FinishNtuple(0);
}

MyRunAction::~MyRunAction(){}

void MyRunAction::BeginOfRunAction(const G4Run * run)
{
    const MyPrimaryGenerator * primaryGenerator = static_cast < const MyPrimaryGenerator *> (G4RunManager::GetRunManager() -> GetUserPrimaryGeneratorAction()); 

    // G4AnalysisManager * analysisManager = G4AnalysisManager::Instance();
    // G4int runID = run -> GetRunID();
    // std::stringstream strRunID;
    // strRunID << runID;
    // analysisManager -> OpenFile("Output" + strRunID.str() + ".root");
    
    if (primaryGenerator) 
    { 
        G4ParticleDefinition * particle = primaryGenerator -> GetParticleGun() -> GetParticleDefinition();
        G4double energy                 = primaryGenerator -> GetParticleGun() -> GetParticleEnergy();
        fRun -> SetPrimary(particle, energy);
    }
}

G4Run * MyRunAction::GenerateRun()
{ 
    fRun = new Run(); 
    return fRun;
}

void MyRunAction::EndOfRunAction(const G4Run *)
{
    // G4AnalysisManager * analysisManager = G4AnalysisManager::Instance();
    // analysisManager -> Write();
    // analysisManager -> CloseFile();

    if (isMaster) 
        fRun -> EndOfRun();
}