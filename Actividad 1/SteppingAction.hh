#ifndef SteppingAction_hh
#define SteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "G4RunManager.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "Run.hh"

class MySteppingAction : public G4UserSteppingAction
{
    public:
        MySteppingAction(MyEventAction * eventAction);
        ~ MySteppingAction();

        virtual void UserSteppingAction(const G4Step *);
    
    private:
        MyEventAction * fEventAction;
};

#endif