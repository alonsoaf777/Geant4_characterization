#ifndef G4_PCM_DETECTOR_CONSTRUCTION_H
#define G4_PCM_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"

namespace G4_PCM {

    class DetectorConstruction : public G4VUserDetectorConstruction {
    public:
        DetectorConstruction();
        virtual ~DetectorConstruction();

        G4VPhysicalVolume* Construct() override;

        G4LogicalVolume* GetGammaDetector() const;

        void SetTargetThickness(G4double thickness);

    private:
        G4LogicalVolume* fGammaDetector;
        G4double fTargetThickness;
    };

}

#endif // G4_PCM_DETECTOR_CONSTRUCTION_H
