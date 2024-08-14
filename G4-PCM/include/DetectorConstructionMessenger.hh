#ifndef G4_PCM_DETECTOR_CONSTRUCTION_MESSENGER_H
#define G4_PCM_DETECTOR_CONSTRUCTION_MESSENGER_H 1

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

namespace G4_PCM
{
    class DetectorConstruction;  // Forward declaration

    class DetectorConstructionMessenger : public G4UImessenger
    {
    public:
        DetectorConstructionMessenger(DetectorConstruction* det);
        ~DetectorConstructionMessenger() override;

        void SetNewValue(G4UIcommand* command, G4String newValue) override;

    private:
        DetectorConstruction* fDetectorConstruction;
        G4UIcmdWithADoubleAndUnit* fTargetThicknessCmd;
    };
}

#endif
