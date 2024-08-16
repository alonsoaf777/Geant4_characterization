#include "DetectorConstruction.hh"
#include "DetectorConstructionMessenger.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
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
        // Construct the world volume
        G4NistManager* nist = G4NistManager::Instance();
        G4double worldSize = 1 * m;
        G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

        auto solidWorld = new G4Box("World", worldSize / 2, worldSize / 2, worldSize);
        auto logicWorld = new G4LogicalVolume(solidWorld, vacuum, "World");
        auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

        // Create the target
        G4Material* target = nist->FindOrBuildMaterial("G4_W");

        G4double innerTargetRadius = 0.0;
        G4double outerTargetRadius = 1.5 * cm;
        G4double targetThickness = 60 * nm;

        auto solidTarget = new G4Tubs("Target", innerTargetRadius, outerTargetRadius, targetThickness / 2.0, 0.0, 360.0 * deg);
        auto logicTarget = new G4LogicalVolume(solidTarget, target, "Target");

        G4ThreeVector targetPos = G4ThreeVector();
        auto targetRotation = new G4RotationMatrix();

        new G4PVPlacement(targetRotation, targetPos, logicTarget, "Target", logicWorld, false, 0);

        // Create the detector
        G4Material* E_PbWO4 = new G4Material("E_PbWO4", 8.28 * g / cm3, 3);
        E_PbWO4->AddElement(nist->FindOrBuildElement("Pb"), 1);
        E_PbWO4->AddElement(nist->FindOrBuildElement("W"), 1);
        E_PbWO4->AddElement(nist->FindOrBuildElement("O"), 4);

        auto solidDetector = new G4Box("Detector", 20 * cm, 20 * cm, 5 * cm);
        auto logicDetector = new G4LogicalVolume(solidDetector, E_PbWO4, "Detector");

        G4ThreeVector detectorPos = G4ThreeVector(0, 0, 20 * cm);
        auto detRotation = new G4RotationMatrix();

        new G4PVPlacement(detRotation, detectorPos, logicDetector, "Detector", logicWorld, false, 0);

        fGammaDetector = logicDetector;

        return physWorld;
    }

    void DetectorConstruction::SetTargetThickness(G4double thickness)
    {
        targetThickness = thickness;
        UpdateGeometry();  // Llama a UpdateGeometry para actualizar la geometría
    }

    void DetectorConstruction::UpdateGeometry()
    {
        // Lógica para actualizar la geometría si es necesario
        G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
    }

    G4LogicalVolume* DetectorConstruction::GetGammaDetector() const
    {
        return fGammaDetector;
    }
}
