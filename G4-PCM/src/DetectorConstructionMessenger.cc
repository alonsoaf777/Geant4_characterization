#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"

namespace G4_PCM
{
    DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* detector)
        : fDetectorConstruction(detector)
    {
        fTargetThicknessCmd = new G4UIcmdWithADoubleAndUnit("/det/setTargetThickness", this);
        fTargetThicknessCmd->SetGuidance("Set the target thickness.");
        fTargetThicknessCmd->SetParameterName("thickness", true);
        // fTargetThicknessCmd->SetDefaultValue(80.0);
        fTargetThicknessCmd->SetDefaultUnit("nm");
        fTargetThicknessCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    }

    DetectorConstructionMessenger::~DetectorConstructionMessenger()
    {
        delete fTargetThicknessCmd;
    }

    void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
    {
        if (command == fTargetThicknessCmd)
        {
            fDetectorConstruction->SetTargetThickness(fTargetThicknessCmd->GetNewDoubleValue(newValue));
        }
    }
}
