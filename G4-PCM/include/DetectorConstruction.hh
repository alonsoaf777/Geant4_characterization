#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"
#include "G4UIcmdWithADoubleAndUnit.hh" // Para comandos de macro

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class DetectorConstructionMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    void SetTargetThickness(G4double thickness);

private:
    DetectorConstructionMessenger* fDetectorMessenger;
    G4LogicalVolume* fGammaDetector;
    G4double fTargetThickness; // Almacena el grosor del objetivo
};

#endif // DetectorConstruction_hh
