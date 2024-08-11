#ifndef PHYSICS_HH
#define PHYSICS_HH	

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicsConstructor.hh"

//Particles 

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
public: 
	MyPhysicsList(); 
	~MyPhysicsList(); 
	
	//Function to set cuts of secundary particles
	void SetCuts() override; 
	//Function to construct particles
	void ConstructParticle() override; 
	
private: 
	G4VPhysicsConstructor *fEmPhysicsList = nullptr; 
	G4String fEmName; 
};

#endif
