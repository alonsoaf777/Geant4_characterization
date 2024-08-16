#ifndef DETECTORCONSTRUCTIONMESSENGER_HH
#define DETECTORCONSTRUCTIONMESSENGER_HH

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

namespace G4_PCM
{
    class DetectorConstruction;

    class DetectorConstructionMessenger : public G4UImessenger
    {
    public:
        DetectorConstructionMessenger(DetectorConstruction* detector);
        ~DetectorConstructionMessenger() override;

        void SetNewValue(G4UIcommand* command, G4String newValue) override;

    private:
        DetectorConstruction* fDetectorConstruction;
        G4UIcmdWithADoubleAndUnit* fTargetThicknessCmd;
        G4UIcmdWithoutParameter* fUpdateGeometryCmd;  // Nuevo comando
    };
}

#endif
