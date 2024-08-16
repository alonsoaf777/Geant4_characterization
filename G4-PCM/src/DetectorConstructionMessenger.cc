#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4RunManager.hh"  // Aseg�rate de incluir este encabezado para G4RunManager

namespace G4_PCM
{
    DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* detConstruction)
        : fDetectorConstruction(detConstruction)
    {
        fTargetThicknessCmd = new G4UIcmdWithADouble("/detector/setTargetThickness", this);
        fTargetThicknessCmd->SetParameterName("thickness", false);
        fTargetThicknessCmd->SetDefaultValue(80.0);
        fTargetThicknessCmd->SetRange("thickness > 0.0");
    }

    DetectorConstructionMessenger::~DetectorConstructionMessenger()
    {
        delete fTargetThicknessCmd;  // Aseg�rate de que fTargetThicknessCmd es un puntero
    }

    void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
    {
        if (command == fTargetThicknessCmd)
        {
            G4double newThickness = fTargetThicknessCmd->GetNewDoubleValue(newValue);
            fDetectorConstruction->SetTargetThickness(newThickness);
            // UpdateGeometry is now called within SetTargetThickness
        }
    }
}
