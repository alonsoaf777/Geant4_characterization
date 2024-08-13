#include "EventAction.hh"

MyEventAction::MyEventAction(MyRunAction *) { fEDep = 0.0; }
MyEventAction::~MyEventAction(){}

void MyEventAction::BeginOfEventAction(const G4Event *) { fEDep = 0.0; }

void MyEventAction::EndOfEventAction(const G4Event *) 
{ 
    G4cout << "Energy deposition: " << fEDep << G4endl; 
    G4AnalysisManager * analysisManager = G4AnalysisManager::Instance();
    analysisManager -> FillNtupleDColumn(2, 0, fEDep);
    analysisManager -> AddNtupleRow(2);
}