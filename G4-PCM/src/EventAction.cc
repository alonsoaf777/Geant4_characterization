
#include "EventAction.hh"
#include "G4AnalysisManager.hh"

namespace G4_PCM {
	EventAction::EventAction(RunAction*) {
		fEnergy = 0.;
	}

	void EventAction::BeginOfEventAction(const G4Event* anEvent) {
		// begin of event actions here
		fEnergy = 0.;

	}
	
	// setting energy and position
	void EventAction::AddEnergy(G4double e) { fEnergy += e; }
	void EventAction::SetPosition(G4ThreeVector p) { fPosition = p; } // Checar esto

	void EventAction::EndOfEventAction(const G4Event* anEvent) {
		// if there was any energy deposited, tell the analysis manager.
		G4AnalysisManager *man = G4AnalysisManager::Instance(); 
	
		man->FillNtupleDColumn(0, 0, fEnergy); 
		man->AddNtupleRow(0); 
	
	}

	void EventAction::Print() {
		G4cout
			<< "Energy: "
			<< G4BestUnit(fEnergy, "Energy")
			// << "Position: "
			// << G4BestUnit(fPosition.getX(), "Length")
			// << G4BestUnit(fPosition.getY(), "Length")
			// << G4BestUnit(fPosition.getZ(), "Length")
			<< G4endl;
	}


	}
