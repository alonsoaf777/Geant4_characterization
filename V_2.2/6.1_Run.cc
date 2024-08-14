#include <iomanip>

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4EmCalculator.hh"
#include "G4Gamma.hh"

#include "6.1_Run.hh"
#include "3.0_DetectorConstruction.hh"
#include "5_PrimaryGenerator.hh"

Run::Run(MyDetectorConstruction * det): fDetector(det){}
Run::~Run(){}

void Run::SetPrimary(G4ParticleDefinition * particle, G4double energy)
{ 
    fParticle = particle;
    fEkin = energy;
}

void Run::CountProcesses(G4String procName) 
{
    std::map <G4String, G4int> ::iterator it = fProcCounter.find(procName);
    if ( it == fProcCounter.end()) 
    {
        fProcCounter[procName] = 1;
    }
    else 
    {
        fProcCounter[procName]++; 
    }
}

void Run::EndOfRun()
{
    G4int prec = 5; 
	G4int dfprec = G4cout.precision(prec);

    G4String partName     = fParticle -> GetParticleName();    
    G4Material * material = fDetector -> GetMaterial();
    G4double density      = material  -> GetDensity();
    G4double thickness    = fDetector -> GetThickness();
        
    G4cout << "\n ======================== run summary ======================\n";

    G4cout << "\n The run is: " << numberOfEvent << " " << partName << " of "
            << G4BestUnit(fEkin, "Energy") << " through " 
            << G4BestUnit(thickness, "Length") << " of "
            << material -> GetName() << " (density: " 
            << G4BestUnit(density, "Volumic Mass") << ")" << G4endl;

    G4int totalCount = 0;
    G4int survive = 0;  
    G4cout << "\n Process calls frequency --->";
    std::map < G4String, G4int >::iterator it;  
    
    for (it = fProcCounter.begin(); it != fProcCounter.end(); it++) 
    {
        G4String procName = it -> first;
        G4int    count    = it -> second;
        totalCount += count; 
        G4cout << "\t" << procName << " = " << count;
        if (procName == "Transportation") survive = count;
    }
    G4cout << G4endl;

    if (totalCount == 0) { G4cout.precision(dfprec);   return;};  

    G4double ratio = double(survive)/totalCount;

    G4cout << "\n Nb of incident particles unaltered after "
            << G4BestUnit(thickness,"Length") << " of "
            << material -> GetName() << " : " << survive 
            << " over " << totalCount << " incident particles."
            << "  Ratio = " << 100 * ratio << " %" << G4endl;
    
    if (ratio == 0.0) return;
    
    G4double CrossSection = - std::log(ratio)/thickness;     
    G4double massicCS  = CrossSection/density;
    
    G4cout << " ---> CrossSection per volume:\t" << CrossSection*cm << " cm^-1 "
            << "\tCrossSection per mass: " << G4BestUnit(massicCS, "Surface/Mass")
            << G4endl;

    fProcCounter.clear(); // remove all contents in fProcCounter 
    G4cout.precision(dfprec); //restore default format
}

void Run::Merge(const G4Run * run)
{
  const Run * localRun = static_cast <const Run*> (run);

  // pass information about primary particle
  fParticle = localRun -> fParticle;
  fEkin     = localRun -> fEkin;
      
  std::map<G4String,G4int>::const_iterator it;
  for (it  = localRun -> fProcCounter.begin(); 
       it != localRun -> fProcCounter.end(); ++it) 
    {
        G4String procName = it -> first;
        G4int localCount  = it -> second;

        if ( fProcCounter.find(procName) == fProcCounter.end()) 
        {
            fProcCounter[procName] = localCount;
        }
        else 
        {
            fProcCounter[procName] += localCount;
        }         
    }
  
  G4Run::Merge(run); 
} 