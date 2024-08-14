#include "DetectorConstruction.hh"
#include "DetectorConstructionMessenger.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh" // Aseg�rate de incluir esto
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
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

    void DetectorConstruction::SetTargetThickness(G4double thickness)
    {
        targetThickness = thickness;
        // Aqu� puedes implementar l�gica adicional para actualizar el dise�o si es necesario
        G4RunManager::GetRunManager()->ReinitializeGeometry();
    }

    G4VPhysicalVolume* DetectorConstruction::Construct()
    {
        G4NistManager* nist = G4NistManager::Instance();

        G4double worldSize = 1 * m;
        G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

        auto solidWorld = new G4Box("World", worldSize / 2, worldSize / 2, worldSize);
        auto logicWorld = new G4LogicalVolume(solidWorld, vacuum, "World");
        auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

        G4double innerTargetRadius = 0.0;
        G4double outerTargetRadius = 1.5 * cm;

        G4Tubs* solidTarget = new G4Tubs("Target", innerTargetRadius, outerTargetRadius, targetThickness / 2.0, 0.0, 360.0 * deg);
        G4Material* targetMaterial = nist->FindOrBuildMaterial("G4_W");
        G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, targetMaterial, "Target");
        G4ThreeVector targetPos = G4ThreeVector();
        G4RotationMatrix* targetRotation = new G4RotationMatrix();
        new G4PVPlacement(targetRotation, targetPos, logicTarget, "Target", logicWorld, false, 0);

        G4double detectorSizeXY = 20 * cm;
        G4double detectorSizeZ = 5 * cm;

        G4Material* E_PbWO4 = new G4Material("E_PbWO4", 8.28 * g / cm3, 3);
        E_PbWO4->AddElement(nist->FindOrBuildElement("Pb"), 1);
        E_PbWO4->AddElement(nist->FindOrBuildElement("W"), 1);
        E_PbWO4->AddElement(nist->FindOrBuildElement("O"), 4);

        G4Box* solidDetector = new G4Box("Detector", detectorSizeXY, detectorSizeXY, detectorSizeZ);
        G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, E_PbWO4, "Detector");
        G4ThreeVector detectorPos = G4ThreeVector(0, 0, 20 * cm);
        G4RotationMatrix* detRotation = new G4RotationMatrix();
        new G4PVPlacement(detRotation, detectorPos, logicDetector, "Detector", logicWorld, false, 0);

        fGammaDetector = logicDetector;

        return physWorld;
    }
}
