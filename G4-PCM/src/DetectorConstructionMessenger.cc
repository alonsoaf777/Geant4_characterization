#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UImanager.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

namespace G4_PCM
{
    DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* detector)
        : G4UImessenger(), fDetectorConstruction(detector)
    {
        fSetTargetThicknessCmd = new G4UIcmdWithADoubleAndUnit("/detector/setTargetThickness", this);
        fSetTargetThicknessCmd->SetGuidance("Set the thickness of the target.");
        fSetTargetThicknessCmd->SetParameterName("Thickness", false);
        fSetTargetThicknessCmd->SetUnitCategory("Length");
        fSetTargetThicknessCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    }

    DetectorConstructionMessenger::~DetectorConstructionMessenger()
    {
        delete fSetTargetThicknessCmd;
    }

    void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
    {
        if (command == fSetTargetThicknessCmd)
        {
            fDetectorConstruction->SetTargetThickness(fSetTargetThicknessCmd->GetNewDoubleValue(newValue));
            fDetectorConstruction->UpdateGeometry();
        }
    }
}
