#ifndef G4_PCM_EVENT_ACTION_HH
#define G4_PCM_EVENT_ACTION_HH

/*
Class description:

An Event represents one single particle (for now.) As the particle enters
The detector, it will continue to deposit energy until it is stopped. All
that energy will be summed up and kept track of here in the form of a "Hit."
*/

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "RunAction.hh"


namespace G4_PCM {

	class EventAction : public G4UserEventAction {
	public:
		EventAction(RunAction*);
		~EventAction() override = default;

		void BeginOfEventAction(const G4Event* anEvent) override;
		void EndOfEventAction(const G4Event* anEvent) override;

		void AddEnergy(G4double energy);
		void SetPosition(G4ThreeVector pos);

		void Print();

	private:
		G4double fEnergy;
		G4ThreeVector fPosition;
	};

	
}

#endif // !G4_PCM_EVENT_ACTION_HH
