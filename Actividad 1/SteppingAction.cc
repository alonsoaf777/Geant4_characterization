#include "SteppingAction.hh"
#include "Run.hh"
#include "G4RunManager.hh"

MySteppingAction::MySteppingAction(MyEventAction * eventAction) { fEventAction = eventAction; }
MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step * step)
{
    G4LogicalVolume * Volume = step -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume() -> GetLogicalVolume();
    const MyDetectorConstruction * detectorConstruction = static_cast < const MyDetectorConstruction *> (G4RunManager::GetRunManager() -> GetUserDetectorConstruction());
    G4LogicalVolume * fScoringVolume = detectorConstruction -> GetScoringVolume();

    if(Volume != fScoringVolume) { return; }

    G4double EDep = step -> GetTotalEnergyDeposit();
    fEventAction -> AddEdep(EDep);

    // EM13 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
    G4StepPoint * endPoint = step -> GetPostStepPoint();
    G4String procName = endPoint -> GetProcessDefinedStep() -> GetProcessName();
  
    Run * run = static_cast <Run *> (G4RunManager::GetRunManager() -> GetNonConstCurrentRun()); 
    run -> CountProcesses(procName);  
            
    // kill event after first interaction
    G4RunManager::GetRunManager() -> AbortEvent();  
    // EM13 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
    
}