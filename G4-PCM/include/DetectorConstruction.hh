#ifndef G4_PCM_DETECTOR_CONSTRUCTION_H
#define G4_PCM_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

namespace G4_PCM
{
    class DetectorConstructionMessenger; // Forward declaration

    class DetectorConstruction : public G4VUserDetectorConstruction
    {
    public:
        DetectorConstruction();
        ~DetectorConstruction() override;

        G4VPhysicalVolume* Construct() override;

        void SetTargetThickness(G4double thickness);

        G4LogicalVolume* GetGammaDetector() const { return fGammaDetector; }

    private:
        G4LogicalVolume* fGammaDetector = nullptr;
        G4double fTargetThickness = 60 * mm; // Valor predeterminado

        G4UIcmdWithADoubleAndUnit* fTargetThicknessCmd;
        DetectorConstructionMessenger* fMessenger; // Pointer to the messenger
    };
}

#endif
