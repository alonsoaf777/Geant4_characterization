#include "crossrun.hh"

CrossRun::CrossRun(MyDetectorConstruction *det) : fDetector(det)
{}

CrossRun::~CrossRun()
{}

void CrossRun::SetPrimary(G4ParticleDefinition *particle, G4double energy)
{
	fParticle = particle; 
	fEkin = energy; 
}

void CrossRun::CountProcesses(G4String procName)
{
	std::map<G4String, G4int>::iterator it = fProcCounter.find(procName); 
	if (it == fProcCounter.end())
	{
		fProcCounter[procName] = 1; 
	}
	else
	{
		fProcCounter[procName]++; 
	}
}

//void Merge

void CrossRun::EndOfRun()
{
	//Ni idea xd
	G4int prec = 5; 
	G4int dfprec = G4cout.precision(prec);
	
	//Obtain the material properties of the target and particle gun
	G4String partName = fParticle->GetParticleName(); 
	G4Material *material = fDetector->GetMaterial(); 
	G4double density = material->GetDensity(); 
	G4double thickness = fDetector->GetThickness(); 
	
	G4cout << "\n ======================== run summary ======================\n";
 	G4cout << "\n The run is: " << numberOfEvent << " " << partName << " of "
        << G4BestUnit(fEkin,"Energy") << " through " 
        << G4BestUnit(thickness,"Length") << " of "
        << material->GetName() << " (density: " 
        << G4BestUnit(density,"Volumic Mass") << ")" << G4endl;
        
        //Frecuency
        //frequency of processes
	  G4int totalCount = 0;
	  G4int survive = 0;  
	  G4cout << "\n Process calls frequency --->";
	  std::map<G4String,G4int>::iterator it;  
	  for (it = fProcCounter.begin(); it != fProcCounter.end(); it++) {
	     G4String procName = it->first;
	     G4int    count    = it->second;
	     totalCount += count; 
	     G4cout << "\t" << procName << " = " << count;
	     if (procName == "Transportation") survive = count;
	  }
	  G4cout << G4endl;
        
        
}
