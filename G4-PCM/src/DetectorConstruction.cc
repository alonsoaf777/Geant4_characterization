
#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"

namespace G4_PCM
{
	G4VPhysicalVolume* DetectorConstruction::Construct()
	{
		// construct our detectors here


        // Get nist material manager
        G4NistManager* nist = G4NistManager::Instance();

        // Refractive indexes

        G4double renergy[2] = { 1.239841939 * eV / 0.2, 1.239841939 * eV / 0.9 };
        G4double rindexLT[2] = { 2.16, 2.16 };
        G4double rindexWorld[2] = { 1.0, 1.0 };

		// Start with constructing the world:
        G4double worldSize = 1 * m;
        G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

        //G4MaterialPropertiesTable* mptWorld = new G4MaterialPropertiesTable();
        //mptWorld->AddProperty("RINDEX", renergy, rindexWorld, 2);

        // Quitar o poner
        //vacuum->SetMaterialPropertiesTable(mptWorld);

        auto solidWorld = new G4Box("World",
            worldSize / 2,
            worldSize / 2,
            worldSize);

        auto logicWorld = new G4LogicalVolume(solidWorld,
            vacuum, 
            "World");

        auto physWorld = new G4PVPlacement(nullptr,
            G4ThreeVector(), 
            logicWorld, 
            "World", 
            nullptr, 
            false, 
            0);


        // create our target target
        G4Material* target = nist->FindOrBuildMaterial("G4_W");

        ////G4double target_hx = 0.9 * cm;
        ////G4double target_hy = 0.9 * cm;
        ////G4double target_hz = 0.05 * mm;

        ////G4Box* solidTarget = new G4Box("Target",
        ////    target_hx,
        ////    target_hy,
        ////    target_hz);

        ////G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, 
        ////    target, 
        ////    "Target");

        ////// target position and rotation
        ////G4ThreeVector targetPos = G4ThreeVector(); // 0,0,0
        ////G4RotationMatrix* targetRotation = new G4RotationMatrix();

        ////// place the target in the world
        ////new G4PVPlacement(targetRotation, 
        ////    targetPos, 
        ////    logicTarget, 
        ////    "Target",
        ////    logicWorld, 
        ////    false, 
        ////    0);


        G4double innerTargetRadius = 0.0;
        G4double outerTargetRadius = 1.5 * cm;
        G4double targetThickness = 13 * mm;

        G4Tubs* solidTarget = new G4Tubs("Target",
            innerTargetRadius,
            outerTargetRadius,
            targetThickness / 2.0,
            0.0,
            360.0 * deg);

        G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget,
            target,
            "Target");

        // target position and rotation
        G4ThreeVector targetPos = G4ThreeVector(); // 0,0,0
        G4RotationMatrix* targetRotation = new G4RotationMatrix();

        // place the target in the world
        new G4PVPlacement(targetRotation,
            targetPos,
            logicTarget,
            "Target",
            logicWorld,
            false,
            0);

        //// create a graphite absorber to absorb electrons
        //G4Material* graphite = nist->FindOrBuildMaterial("G4_GRAPHITE");

        //G4double absorber_hx = 0.9;
        //G4double absorber_hy = 0.9 * cm;
        //G4double absorber_hz = 0.05 * cm;

        //G4Box* solidAbsorber = new G4Box("Absorber",
        //    absorber_hx,
        //    absorber_hy,
        //    absorber_hz);

        //G4LogicalVolume* logicAbsorber = new G4LogicalVolume(solidAbsorber,
        //    graphite,
        //    "Absorber");

        //// absorber position and rotation
        //G4double absorberZ = targetPos.getZ() + (absorber_hz / 2);
        //G4ThreeVector absorberPos = G4ThreeVector(0.0, 0.0, absorberZ);
        //G4RotationMatrix* absorberRot = new G4RotationMatrix();

        //// place the absorber
        //new G4PVPlacement(absorberRot,
        //    absorberPos,
        //    logicAbsorber,
        //    "Absorber",
        //    logicWorld,
        //    false,
        //    0);
        

        // Detector
        G4double detectorSizeXY = 20 * cm;
        G4double detectorSizeZ = 5 * cm;

        // detector materials

        // Configure Lead Tungstate for crystals
        G4Material* E_PbWO4 = new G4Material("E_PbWO4", 8.28 * g / cm3, 3);
        E_PbWO4->AddElement(nist->FindOrBuildElement("Pb"), 1);
        E_PbWO4->AddElement(nist->FindOrBuildElement("W"), 1);
        E_PbWO4->AddElement(nist->FindOrBuildElement("O"), 4);


        //G4MaterialPropertiesTable* mptLT = new G4MaterialPropertiesTable();
        //mptLT->AddProperty("RINDEX", renergy, rindexLT, 2);

        // Quitar o poner
        //E_PbWO4->SetMaterialPropertiesTable(mptLT);

        // G4Material* water = nist->FindOrBuildMaterial("G4_WATER");
        // G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");


        G4Box* solidDetector = new G4Box(
            "Detector",
            detectorSizeXY,
            detectorSizeXY,
            detectorSizeZ);

        G4LogicalVolume* logicDetector = new G4LogicalVolume(
            solidDetector,
            E_PbWO4,
            //target,
            //water,
            "Detector");

        G4ThreeVector detectorPos = G4ThreeVector(0, 0, 20 * cm);
        G4RotationMatrix* detRotation = new G4RotationMatrix();


        // place the detector
        new G4PVPlacement(detRotation,
            detectorPos,
            logicDetector,
            "Detector",
            logicWorld,
            false,
            0);

        // Define this detector as the gamma detector
        fGammaDetector = logicDetector;
	
        return physWorld;
    }

}