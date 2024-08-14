#ifndef Run_hh
#define Run_hh

#include "globals.hh"
#include <map>

#include "G4Run.hh"

#include "3.0_DetectorConstruction.hh"
#include "5_PrimaryGenerator.hh"

class Run : public G4Run
{
  public:
    Run();
    ~Run();

  public:
    void SetPrimary(G4ParticleDefinition * particle, G4double energy);
    void CountProcesses(G4String procName);
    void Merge(const G4Run *) override;
    void EndOfRun();

  private:
    G4ParticleDefinition * link_ParticleDefinition = nullptr;
    G4double link_KEnergy = 0.0;

    std::map<G4String,G4int>  fProcCounter;
};

#endif