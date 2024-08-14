#ifndef G4_PCM_DETECTOR_CONSTRUCTION_H
#define G4_PCM_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"

namespace G4_PCM
{
    class DetectorConstruction : public G4VUserDetectorConstruction
    {
    public:
        DetectorConstruction();
        ~DetectorConstruction() override;

        G4VPhysicalVolume* Construct() override;

        G4LogicalVolume* GetGammaDetector() const { return fGammaDetector; }
        void SetTargetThickness(G4double thickness) { fTargetThickness = thickness; }

    private:
        G4LogicalVolume* fGammaDetector = nullptr;
        G4double fTargetThickness;  // Thickness of the target
    };
}

#endif
