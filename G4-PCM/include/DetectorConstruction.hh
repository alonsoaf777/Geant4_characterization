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
        void UpdateGeometry();  // Nuevo m�todo para actualizar la geometr�a

        G4LogicalVolume* GetGammaDetector() const;  // A�adido m�todo getter

    private:
        G4LogicalVolume* fGammaDetector = nullptr;
        G4double targetThickness = 80 * nm;
        DetectorConstructionMessenger* fDetectorMessenger;
    };
}

#endif
