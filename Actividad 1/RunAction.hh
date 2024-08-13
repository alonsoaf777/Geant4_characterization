#ifndef RunAction_hh
#define RunAction_hh

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGenerator.hh"
#include "Run.hh"

class MyDetectorConstruction;
class Run;

class MyRunAction : public G4UserRunAction
{
    public:
        MyRunAction(MyDetectorConstruction *, MyPrimaryGenerator *);
        ~MyRunAction();

        virtual void BeginOfRunAction(const G4Run*) override;
        virtual void EndOfRunAction(const G4Run*) override;

        G4Run * GenerateRun() override;

    private:
        MyDetectorConstruction * fDetector = nullptr;
        MyPrimaryGenerator * fPrimary  = nullptr;
        Run * fRun = nullptr;
};

#endif