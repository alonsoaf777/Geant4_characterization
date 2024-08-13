#include "PrimaryGenerator.hh"
#include "Randomize.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    G4ParticleTable * particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "gamma";
    G4ParticleDefinition * particle = particleTable -> FindParticle(particleName);

    fParticleGun -> SetParticleDefinition(particle);
    fParticleGun -> SetParticleEnergy(1.0 * MeV);
}

MyPrimaryGenerator::~MyPrimaryGenerator() { delete fParticleGun; }

void MyPrimaryGenerator::GeneratePrimaries(G4Event * anEvent)
{ 
    G4double x0, y0, z0;
    G4double radius = 2.0;
    G4double dx0 = radius * cm;
    G4double dy0 = radius * cm;
    // G4double dz0 = radius * cm;
    x0 = dx0 * (G4UniformRand() - 0.5);
    y0 = dy0 * (G4UniformRand() - 0.5);
    // z0 = dz0 * (G4UniformRand() - 0.5);
    G4ThreeVector photonPosition(x0, y0, -15.0);
    fParticleGun -> SetParticlePosition(photonPosition);

    G4double theta, phi;
    theta = (G4UniformRand() - 0.5);
    phi = (G4UniformRand() - 0.5);
    G4ThreeVector photonMomentum(theta, phi, 1.0);
    fParticleGun -> SetParticleMomentumDirection(photonMomentum);

    fParticleGun -> GeneratePrimaryVertex(anEvent); 
}
