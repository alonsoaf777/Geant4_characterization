#ifndef Run_hh
#define Run_hh

#include "G4Run.hh"
#include "globals.hh"
#include <map>

class DetectorConstruction;
class G4ParticleDefinition;

class Run : public G4Run
{
  public:
    Run(DetectorConstruction *);
   ~Run() override = default;

  public:
    void SetPrimary(G4ParticleDefinition * particle, G4double energy);
    void CountProcesses(G4String procName);
    void Merge(const G4Run *) override;
    void EndOfRun();

  private:
    MyDetectorConstruction * fDetector = nullptr;
    G4ParticleDefinition * fParticle = nullptr;
    G4double  fEkin = 0.0;

    std::map<G4String,G4int>  fProcCounter;
};

#endif