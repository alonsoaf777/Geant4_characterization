#include "run.hh"

MyRunAction::MyRunAction()
{
	//Instantiate the analysis manager for outputs
	G4AnalysisManager *man = G4AnalysisManager::Instance(); 
	
	//Create the root data for energy deposition
	man->CreateNtuple("Scoring", "Scoring"); 
	man->CreateNtupleDColumn("fEdep"); 
	man->FinishNtuple(0);
	//For hits
	man->CreateNtuple("Hits", "Hits"); 
	man->CreateNtupleIColumn("fEvent"); 
	man->CreateNtupleDColumn("fX"); 
	man->CreateNtupleDColumn("fY"); 
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(1); 
	
	//Create histogram for cross section
	man->CreateNtuple("CrossSection", "CrossSection");
	man->CreateNtupleDColumn("Cross/Volume cm^-1");
	man->CreateNtupleDColumn("Cross/Mass ");
	man->FinishNtuple(2); 
	 
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance(); 
	
	//Generate a root file with its individual run
	G4int runID = run->GetRunID(); 
	
	std::stringstream strRunID; 
	strRunID << runID; 
	
	man->OpenFile("output" + strRunID.str() + ".root"); 
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance(); 
	
	man->Write(); 
	man->CloseFile(); 
}
