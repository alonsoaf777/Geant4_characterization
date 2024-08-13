#include "ActionInitialization.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGenerator.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

MyActionInitialization::MyActionInitialization(MyDetectorConstruction * det) : fDetector(det){}
MyActionInitialization::~MyActionInitialization(){}

void MyActionInitialization::BuildForMaster() const 
{
    MyRunAction * runAction = new MyRunAction(fDetector, 0);
    SetUserAction(runAction);
}

void MyActionInitialization::Build() const
{
    MyRunAction * runAction = new MyRunAction();
    SetUserAction(runAction);

    MyPrimaryGenerator * generator = new MyPrimaryGenerator();
    SetUserAction(generator);

    MyEventAction * eventAction = new MyEventAction(runAction);
    SetUserAction(eventAction);

    MySteppingAction * steppingAction = new MySteppingAction(eventAction);
    SetUserAction(steppingAction);
}
