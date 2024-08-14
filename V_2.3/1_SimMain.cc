#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UIManager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "2_PhysicsList.hh"
#include "3.0_DetectorConstruction.hh"
#include "4_ActionInitialization.hh"

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
        G4cout << "-----Running in multi-threaded mode------" << G4endl;
    }

    runManager -> SetUserInitialization(new MyDetectorConstruction);
    runManager -> SetUserInitialization(new MyPhysicsList);
    runManager -> SetUserInitialization(new MyActionInitialization); 

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