#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	//Em physics 
	//RegisterPhysics (new G4EmStandardPhysics()); 
	new G4UnitDefinition( "mm2/g", "mm2/g","Surface/Mass", mm2/g);
  	new G4UnitDefinition( "um2/mg", "um2/mg","Surface/Mass", um*um/mg);
  	
	SetVerboseLevel(1); 
	
	G4LossTableManager::Instance(); 
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

#include "G4RayleighScattering.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4KleinNishinaModel.hh"
#include "G4GammaConversion.hh"
#include "G4GammaConversionToMuons.hh"

void MyPhysicsList::ConstructProcess()
{
	AddTransportation(); 
	
	//Access the available particles
	G4ParticleTable *ParticleTable = G4ParticleTable::GetParticleTable(); 
	G4ParticleDefinition *particle = ParticleTable->FindParticle("gamma"); 
	G4ProcessManager *pmanager = particle->GetProcessManager(); 
	G4String particleName = particle->GetParticleName(); 
	
	//Add properties 
	pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
        G4ComptonScattering* compt   = new G4ComptonScattering;
        compt->SetEmModel(new G4KleinNishinaModel());
        pmanager->AddDiscreteProcess(compt);
        pmanager->AddDiscreteProcess(new G4GammaConversion);
        pmanager->AddDiscreteProcess(new G4GammaConversionToMuons);  
        
        // Deexcitation
	  //
	G4VAtomDeexcitation* deex = new G4UAtomicDeexcitation();
	G4LossTableManager::Instance()->SetAtomDeexcitation(deex);
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
