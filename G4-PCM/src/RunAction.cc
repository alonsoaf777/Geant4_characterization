#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4Run.hh"
#include "EventAction.hh" // Include EventAction for access to the static method

namespace G4_PCM {
	RunAction::RunAction() {
		auto analysisManager = G4AnalysisManager::Instance();
		analysisManager->SetDefaultFileType("root");
		analysisManager->SetNtupleMerging(true);
		analysisManager->SetVerboseLevel(4);
		analysisManager->CreateNtuple("G4_PCM", "Hits");
		analysisManager->CreateNtupleDColumn("Energy");
		analysisManager->FinishNtuple();
	}

	RunAction::~RunAction() {
	}

	void RunAction::BeginOfRunAction(const G4Run* aRun) {
		fTimer.Start();
		auto* analysisManager = G4AnalysisManager::Instance();
		G4int runNumber = aRun->GetRunID();
		G4String fileName = "NTuples_Run" + std::to_string(runNumber);
		analysisManager->SetFileName(fileName);
		analysisManager->OpenFile();
	}

	void RunAction::EndOfRunAction(const G4Run* aRun) {
		auto* analysisManager = G4AnalysisManager::Instance();
		analysisManager->Write();
		analysisManager->CloseFile();
		fTimer.Stop();
		PrintTime();

		// Print the total number of ntuple registrations
		G4cout
			<< "Total number of hits registrations: "
			<< EventAction::GetNtupleRegistrationCount()
			<< G4endl;
	}

	void RunAction::PrintTime() {
		auto time = fTimer.GetRealElapsed();
		G4cout
			<< "Elapsed time: "
			<< time
			<< " Seconds."
			<< G4endl;
	}
}
