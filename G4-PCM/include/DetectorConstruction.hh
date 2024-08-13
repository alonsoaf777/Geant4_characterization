#ifndef G4_PCM_DETECTOR_CONSTRUCTION_H
#define G4_PCM_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"

namespace G4_PCM
{
	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction() = default;
		~DetectorConstruction() override = default;

		G4VPhysicalVolume* Construct() override;

		G4LogicalVolume* GetGammaDetector() const { return fGammaDetector; }

	private:
		G4LogicalVolume* fGammaDetector = nullptr;
	};
}


#endif