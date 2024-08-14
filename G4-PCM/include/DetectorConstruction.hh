#ifndef G4_PCM_DETECTOR_CONSTRUCTION_H
#define G4_PCM_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh" // Asegúrate de incluir esto

namespace G4_PCM
{
    class DetectorConstructionMessenger;

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
        G4double targetThickness = 80 * nm; // Asegúrate de usar unidades aquí
        DetectorConstructionMessenger* fDetectorMessenger;
    };
}

#endif
