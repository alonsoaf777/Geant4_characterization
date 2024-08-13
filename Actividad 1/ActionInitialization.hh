#ifndef ACTIONINIT_HH
#define ACTIONINIT_HH

#include "G4VUserActionInitialization.hh"
#include "PrimaryGenerator.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGenerator.hh"
#include "Run.hh"

class MyDetectorConstruction;

class MyActionInitialization : public G4VUserActionInitialization
{
    public:
        MyActionInitialization(MyDetectorConstruction *);
        ~MyActionInitialization();

        virtual void Build() const;
        virtual void BuildForMaster() const;
    
    private:
        DetectorConstruction * fDetector = nullptr;
};

#endif