#include "DetectorConstruction.hh"
#include "DetectorConstructionMessenger.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

namespace G4_PCM
{
    DetectorConstruction::DetectorConstruction()
        : G4VUserDetectorConstruction(),
        fGammaDetector(nullptr),
        targetThickness(80 * nm),
        fDetectorMessenger(new DetectorConstructionMessenger(this))
    {
    }

    DetectorConstruction::~DetectorConstruction()
    {
        delete fDetectorMessenger;
    }

    G4VPhysicalVolume* DetectorConstruction::Construct()
    {
        G4NistManager* nist = G4NistManager::Instance();
        G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

        G4Box* solidWorld = new G4Box("World", 1.0 * m, 1.0 * m, 1.0 * m);
        G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World");

        G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

        // Aquí construyes tu detector gamma usando `targetThickness`
        G4Box* solidDetector = new G4Box("GammaDetector", 0.5 * m, 0.5 * m, targetThickness / 2);
        fGammaDetector = new G4LogicalVolume(solidDetector, air, "GammaDetector");

        new G4PVPlacement(0, G4ThreeVector(), fGammaDetector, "GammaDetector", logicWorld, false, 0, true);

        return physWorld;
    }

    void DetectorConstruction::SetTargetThickness(G4double thickness)
    {
        targetThickness = thickness;
    }

    void DetectorConstruction::UpdateGeometry()
    {
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }
}
