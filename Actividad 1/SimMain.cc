#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UIManager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int isArgcOne = false;

int main(int argc, char** argv)
{
    isArgcOne = (argc);

    G4RunManager * runManager;

    if (argc == 1) 
    {
        runManager = new G4RunManager();
        G4cout << "-----Running in single-threaded mode-----" << G4endl;
    } 
    else 
    {
        runManager = new G4MTRunManager();
        // runManager -> SetNumberOfThreads(8);
        G4cout << "-----Running in multi-threaded mode------" << G4endl;
    }

    MyDetectorConstruction * det = new MyDetectorConstruction;

    runManager -> SetUserInitialization(det);
    runManager -> SetUserInitialization(new MyPhysicsList);
    runManager -> SetUserInitialization(new MyActionInitialization(det)); 

    // runManager -> Initialize();

    G4VisManager * visManager = new G4VisExecutive();
    visManager -> Initialize();
    G4UImanager * UImanager = G4UImanager::GetUIpointer();

    G4UIExecutive * UI = 0;
    
    if(argc == 1)
    {
        UI = new G4UIExecutive(argc, argv);
        UImanager -> ApplyCommand("/control/execute Visualization.mac");
        UI -> SessionStart();
    }
    else
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager -> ApplyCommand(command + fileName);
    }

    return 0;
}






// G4MTRunManager * runManager = new G4MTRunManager;
// runManager -> SetNumberOfThreads(8);
// runManager -> Initialize();

// UImanager -> ApplyCommand("/vis/open OGL");
// UImanager -> ApplyCommand("/vis/drawVolume");
// UImanager -> ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
// UImanager -> ApplyCommand("/vis/viewer/set/autoRefresh true");
// UImanager -> ApplyCommand("/vis/scene/add/trajectories smooth");
// UImanager -> ApplyCommand("/vis/scene/endOfEventAction accumulate");

// #if(argc == 1)
//       G4RunManager * runManager = new G4RunManager; 
//       G4cout << "---------single---------" << G4endl;
// #else
//       G4MTRunManager * runManager = new G4MTRunManager;
//       G4cout << "---------multi---------" << G4endl;
// #endif

// #if(argc == 1)
  // runManager -> Initialize();
// #endif