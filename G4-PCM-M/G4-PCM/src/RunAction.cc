
#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4Run.hh" // This is to access the run number


namespace G4_PCM {
	RunAction::RunAction() {

		// access analysis manager
		auto analysisManager = G4AnalysisManager::Instance();

		// set default settings
		analysisManager->SetDefaultFileType("root");
		analysisManager->SetNtupleMerging(true);
		analysisManager->SetVerboseLevel(4); // It was 0
		// analysisManager->SetFileName("NTuples");

		// create nTuple to store the data:
		analysisManager->CreateNtuple("G4_PCM", "Hits");
		// The letters D, I, S, F correspond to types
		analysisManager->CreateNtupleDColumn("Energy"); //   id = 0
		// analysisManager->CreateNtupleDColumn("PositionX"); //id = 1
		// analysisManager->CreateNtupleDColumn("PositionY"); //id = 2
		// analysisManager->CreateNtupleDColumn("PositionZ"); //id = 3
		analysisManager->FinishNtuple();

	}

	RunAction::~RunAction() {
	}

	void RunAction::BeginOfRunAction(const G4Run* aRun) {
		// start time
		fTimer.Start();

		auto *analysisManager = G4AnalysisManager::Instance();

		// Get the run number
		G4int runNumber = aRun->GetRunID();

		// Set the file name including the run number
		G4String fileName = "NTuples_Run" + std::to_string(runNumber);
		analysisManager->SetFileName(fileName);

		// Open the file
		analysisManager->OpenFile();
	}

	void RunAction::EndOfRunAction(const G4Run* aRun) {

		auto *analysisManager = G4AnalysisManager::Instance();

		// write to output file
		analysisManager->Write();
		analysisManager->CloseFile();

		// end time
		fTimer.Stop();

		// print out the time it took
		PrintTime();
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
