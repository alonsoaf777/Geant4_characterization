#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4GenericMessenger.hh"

#include "DetectorAction.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        MyDetectorConstruction();
        ~MyDetectorConstruction();

        G4LogicalVolume * GetScoringVolume() const {return fScoringVolume;}

        virtual G4VPhysicalVolume * Construct();
    
    private:
        G4LogicalVolume * logicDetector;
        virtual void ConstructSDandField();
        
        G4Box * solidWorld, * solidDetector, * solidRadiator;
        G4LogicalVolume * logicWorld, * logicRadiator;
        G4VPhysicalVolume * physicalWorld, * physicalRadiator, * physicalDetector;

        G4LogicalVolume * fScoringVolume;

        void DefineMaterials();

        G4Material * SiO2, * H2O, * Aerogel, * worldMaterial, * Aluminum, * Air;
        G4Element * C, * Al, * N, * O;

        G4int nColumns, nRows;
        G4GenericMessenger * fDetectorMessenger;  
};

#endif 