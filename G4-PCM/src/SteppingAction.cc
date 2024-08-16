#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"

namespace G4_PCM {

    SteppingAction::SteppingAction(EventAction* eventAction) {
        const auto detConstruction = static_cast<const DetectorConstruction*>(
            G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fGammaDetector = detConstruction->GetGammaDetector();

        if (eventAction) {
            feventAction = eventAction;
        }
    }

    SteppingAction::~SteppingAction() {}

    void SteppingAction::UserSteppingAction(const G4Step* step) {
        G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

        if (volume != fGammaDetector) return;

        if (step->IsFirstStepInVolume()) {
            feventAction->SetPosition(step->GetPreStepPoint()->GetPosition());
        }

        feventAction->AddEnergy(step->GetTotalEnergyDeposit());
    }

}
