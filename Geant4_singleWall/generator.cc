#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	//Create the particle gun
	fParticleGun = new G4ParticleGun(1); 
	
	//Access the available particles
	G4ParticleTable *ParticleTable = G4ParticleTable::GetParticleTable(); 
	
	//Properties of the table
	G4ParticleDefinition *particle = ParticleTable->FindParticle("gamma"); 
	fParticleGun->SetParticleEnergy(100 * MeV); 
	//Position
	G4double minX = -50*cm, maxX = 50*cm; 
	G4double minY = -50*cm, maxY = 50*cm;
	
	// Generate random position within the world volume
   	G4double posX = G4UniformRand() * (maxX - minX) + minX;
    	G4double posY = G4UniformRand() * (maxY - minY) + minY;
	G4double zpos = -35*cm;  
	
	G4ThreeVector gunPosition(posX, posY, zpos); 
	fParticleGun->SetParticlePosition(gunPosition);
	
	//Direction
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction()); 
	
	G4ThreeVector targetPosition = detectorConstruction->GetTargetPosition(); 
	
	G4ThreeVector direction = (targetPosition - gunPosition).unit(); 
	
	fParticleGun->SetParticleMomentumDirection(direction); 
	fParticleGun->SetParticleDefinition(particle);  

}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun; 
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	//Generate the particle
	fParticleGun->GeneratePrimaryVertex(anEvent); 
}
