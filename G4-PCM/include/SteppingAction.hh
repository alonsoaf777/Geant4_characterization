#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

namespace G4_PCM
{
    class DetectorConstruction;

    class SteppingAction : public G4UserSteppingAction
    {
    public:
        SteppingAction();
        ~SteppingAction() override;

        void UserSteppingAction(const G4Step* step) override;

    private:
        DetectorConstruction* fDetectorConstruction;  // Corregido para puntero a DetectorConstruction
    };
}

#endif
