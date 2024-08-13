#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGenerator.hh"
#include "Run.hh"

class MyDetectorConstruction;

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
    public:
        MyPrimaryGenerator(MyDetectorConstruction *);
        ~MyPrimaryGenerator();

        virtual void GeneratePrimaries(G4Event*);
        G4ParticleGun * GetParticleGun() const {return fParticleGun;}
    
    private:
        G4ParticleGun * fParticleGun;
};

#endif