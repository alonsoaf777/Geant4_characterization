#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

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
        void UpdateGeometry();  // Nuevo método para actualizar la geometría

        G4LogicalVolume* GetGammaDetector() const;  // Añadido método getter

    private:
        G4LogicalVolume* fGammaDetector = nullptr;
        G4double targetThickness = 80 * nm;
        DetectorConstructionMessenger* fDetectorMessenger;
    };
}

#endif
