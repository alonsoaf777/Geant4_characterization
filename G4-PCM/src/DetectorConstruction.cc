#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UImanager.hh"

DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* detector)
    : G4UImessenger(),
    fDetectorConstruction(detector)
{
    // Directorio de comandos
    G4UIdirectory* detDir = new G4UIdirectory("/detector/");
    detDir->SetGuidance("Detector construction commands");

    // Comando para el grosor del objetivo
    fTargetThicknessCmd = new G4UIcmdWithADoubleAndUnit("/detector/targetThickness", this);
    fTargetThicknessCmd->SetGuidance("Set target thickness");
    fTargetThicknessCmd->SetParameterName("targetThickness", false);
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
