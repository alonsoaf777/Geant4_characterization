#include "3.0_DetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    fDetectorMessenger = new G4GenericMessenger(this, "/myDetector/", "Detector Construction");
    fDetectorMessenger -> DeclareProperty("nColumns", nColumns, "Number of columns");
    fDetectorMessenger -> DeclareProperty("nRows", nRows, "Number of rows");
    nColumns = 10;
    nRows    = 10;

    DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction(){}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager * nist = G4NistManager::Instance();

    N = new G4Element("Nitrogen", "N", 7, 14.01*g/mole);
    O = new G4Element("Oxygen"  , "O", 8, 16.00*g/mole);

    worldMaterial = nist -> FindOrBuildMaterial("G4_AIR");
    Air = new G4Material("Air", 0.0000000000000000001*g/cm3, 2);
    Air -> AddElement(N, 0.78);
    Air -> AddElement(O, 0.22);

    SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2); 
    SiO2 -> AddElement(nist -> FindOrBuildElement("Si"), 1);
    SiO2 -> AddElement(nist -> FindOrBuildElement("O"), 2);

    H2O = new G4Material("H2O", 1.000*g/cm3, 2); 
    H2O -> AddElement(nist -> FindOrBuildElement("H"), 2);
    H2O -> AddElement(nist -> FindOrBuildElement("O"), 1);

    G4Element * C = nist -> FindOrBuildElement("C");

    Aluminum = new G4Material("Aluminum", 2.70 * g/cm3, 1);
    Aluminum -> AddElement(nist -> FindOrBuildElement("Al"), 1);
    
    Aerogel = new G4Material("Aerogel", 10.000*g/cm3, 3);
    Aerogel -> AddMaterial(SiO2, 62.5*perCent);
    Aerogel -> AddMaterial(H2O , 37.4*perCent);
    Aerogel -> AddElement (C   , 00.1*perCent);

    G4double PhotonEnergy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double RindexAerogel[2] = {1.1, 1.1};
    G4double RindexWorld[2] = {1.0, 1.0};

    G4MaterialPropertiesTable * AerogelProperties = new G4MaterialPropertiesTable();
    AerogelProperties -> AddProperty("RINDEX", PhotonEnergy, RindexAerogel, 2);
    Aerogel -> SetMaterialPropertiesTable(AerogelProperties);
    
    G4MaterialPropertiesTable * worldMaterialProperties = new G4MaterialPropertiesTable();
    worldMaterialProperties -> AddProperty("RINDEX", PhotonEnergy, RindexWorld, 2);
    worldMaterial -> SetMaterialPropertiesTable(worldMaterialProperties);
}

G4VPhysicalVolume * MyDetectorConstruction::Construct()
{
    link_MaterialTarget = Aluminum;
    link_ThicknessTarget = 1*cm; 

    G4double xWorld = 0.5*m;
    G4double yWorld = 0.5*m;
    G4double zWorld = 0.5*m;

    solidWorld = new G4Box("SolidWorld", xWorld, yWorld, zWorld);
    logicWorld = new G4LogicalVolume(solidWorld, Air, "LogicalWorld");
    physicalWorld = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0), logicWorld, "PhysicalWorld", 0, false, 0, true);

    solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, link_ThicknessTarget/2);
    logicRadiator = new G4LogicalVolume(solidRadiator, link_MaterialTarget, "logicalRadiator");
    physicalRadiator = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.25*m), logicRadiator, "PhysicalRadiator", logicWorld, false, 0, true);

    fScoringVolume = logicRadiator;

    solidDetector = new G4Box("solidDetector", xWorld/nRows, yWorld/nColumns, 0.01*m);
    logicDetector = new G4LogicalVolume(solidDetector, worldMaterial, "logicalDetector");

    for(G4int i = 0; i < nRows; i++){
        
        for (G4int j = 0; j < nColumns; j++){
            
            physicalDetector 
            = new G4PVPlacement(0, G4ThreeVector(-0.5*m + (i+0.5)*m/nRows, -0.5*m + (j+0.5)*m/nColumns, 0.49*m), 
            logicDetector, "physicalDetector", logicWorld, false, j + i*nColumns, true);
        }
    }

    return physicalWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector * sensitiveDetector = new MySensitiveDetector("sensitiveDetector");
    logicDetector -> SetSensitiveDetector(sensitiveDetector);
}