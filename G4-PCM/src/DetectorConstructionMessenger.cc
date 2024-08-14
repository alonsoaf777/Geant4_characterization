#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UImanager.hh"

namespace G4_PCM
{
    DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* det)
        : fDetectorConstruction(det)
    {
        // Define the command to set the target thickness
        fTargetThicknessCmd = new G4UIcmdWithADoubleAndUnit("/det/setTargetThickness", this);
        fTargetThicknessCmd->SetGuidance("Set the thickness of the target.");
        fTargetThicknessCmd->SetParameterName("thickness", true);
        fTargetThicknessCmd->SetRange("thickness > 0.");
        fTargetThicknessCmd->SetDefaultValue(80.0);
        fTargetThicknessCmd->SetDefaultUnit("nm");
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
