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
    {
        fDetectorMessenger = new DetectorConstructionMessenger(this);
    }

    DetectorConstruction::~DetectorConstruction()
    {
        delete fDetectorMessenger;
    }

    G4VPhysicalVolume* DetectorConstruction::Construct()
    {
        G4NistManager* nist = G4NistManager::Instance();

        // Definir un mundo sencillo
        G4double world_sizeXYZ = 1.2 * targetThickness;
        G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

        G4Box* solidWorld = new G4Box("World", 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ);

        G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");

        G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

        // Detector de gamma (ejemplo sencillo)
        G4Material* detector_mat = nist->FindOrBuildMaterial("G4_Si");
        G4Box* solidDetector = new G4Box("GammaDetector", 0.5 * targetThickness, 0.5 * targetThickness, 0.5 * targetThickness);

        fGammaDetector = new G4LogicalVolume(solidDetector, detector_mat, "GammaDetector");

        new G4PVPlacement(0, G4ThreeVector(), fGammaDetector, "GammaDetector", logicWorld, false, 0, true);

        return physWorld;
    }

    void DetectorConstruction::SetTargetThickness(G4double thickness)
    {
        targetThickness = thickness;
    }

    void DetectorConstruction::UpdateGeometry()
    {
        G4RunManager::GetRunManager()->GeometryHasBeenModified();
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }
}
