#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"

namespace G4_PCM {
    RunAction::RunAction() {
        // Accede al análisis manager
        auto analysisManager = G4AnalysisManager::Instance();

        // Configuraciones por defecto
        analysisManager->SetDefaultFileType("root");
        analysisManager->SetNtupleMerging(true);
        // Aqui no poner deafault
        analysisManager->SetVerboseLevel(4);

        // Crear nTuple para almacenar datos
        analysisManager->CreateNtuple("G4_PCM", "Hits");
        analysisManager->CreateNtupleDColumn("Energy");     // id = 0
        analysisManager->CreateNtupleDColumn("PositionX");  // id = 1
        analysisManager->CreateNtupleDColumn("PositionY");  // id = 2
        analysisManager->CreateNtupleDColumn("PositionZ");  // id = 3
        analysisManager->FinishNtuple();
    }

    RunAction::~RunAction() {}

    void RunAction::BeginOfRunAction(const G4Run* aRun) {
        // Accede al análisis manager
        auto analysisManager = G4AnalysisManager::Instance();

        // Obtén el número de la corrida y establece el nombre del archivo
        G4int runNumber = aRun->GetRunID();
        G4String fileName = "NTuples_Run" + std::to_string(runNumber);

        // Establece el nombre del archivo y abre el archivo
        analysisManager->SetFileName(fileName);
        analysisManager->OpenFile();

        G4cout << "ROOT file opened for run: " << runNumber << G4endl;
    }

    void RunAction::EndOfRunAction(const G4Run* aRun) {
        auto analysisManager = G4AnalysisManager::Instance();

        // Escribe y cierra el archivo ROOT
        analysisManager->Write();
        analysisManager->CloseFile();

        G4cout << "ROOT file closed for run: " << aRun->GetRunID() << G4endl;
    }

    void RunAction::PrintTime() {
        auto time = fTimer.GetRealElapsed();
        G4cout << "Elapsed time: " << time << " Seconds." << G4endl;
    }
}
