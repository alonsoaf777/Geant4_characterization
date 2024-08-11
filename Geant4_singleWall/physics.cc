#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	//Em physics 
	RegisterPhysics (new G4EmStandardPhysics()); 
}

MyPhysicsList::~MyPhysicsList()
{}

//CONstruct ṕarticles
void MyPhysicsList::ConstructParticle()
{
    G4BosonConstructor  pBosonConstructor;
    pBosonConstructor.ConstructParticle();

    G4LeptonConstructor pLeptonConstructor;
    pLeptonConstructor.ConstructParticle();

    G4MesonConstructor pMesonConstructor;
    pMesonConstructor.ConstructParticle();

    G4BaryonConstructor pBaryonConstructor;
    pBaryonConstructor.ConstructParticle();

    G4IonConstructor pIonConstructor;
    pIonConstructor.ConstructParticle();

    G4ShortLivedConstructor pShortLivedConstructor;
    pShortLivedConstructor.ConstructParticle(); 
} 


//Set Cuts of secundary generated particles
//It helps with computer efficiency
//The particles that are not in the range are not tracked but its energy is still used

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"

void MyPhysicsList::SetCuts()
{
	//Sets limit for cut
	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100*eV, 1*GeV); 
	//Assign them
	G4VUserPhysicsList::SetCuts(); 
	//For debugging print range
	DumpCutValuesTable(); 
}
