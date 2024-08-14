#include "3.0_DetectorConstruction.hh"
#include "5_PrimaryGenerator.hh"
#include "4_ActionInitialization.hh"
#include "6.0_RunAction.hh"
#include "8_SteppingAction.hh"

MyActionInitialization::MyActionInitialization(){}
MyActionInitialization::~MyActionInitialization(){}

void MyActionInitialization::BuildForMaster() const 
{
    MyRunAction * runAction = new MyRunAction();
    SetUserAction(runAction);
}

void MyActionInitialization::Build() const
{
    MyPrimaryGenerator * generator = new MyPrimaryGenerator();
    SetUserAction(generator);
    
    MyRunAction * runAction = new MyRunAction();
    SetUserAction(runAction);

    MyEventAction * eventAction = new MyEventAction(runAction);
    SetUserAction(eventAction);

    MySteppingAction * steppingAction = new MySteppingAction(eventAction);
    SetUserAction(steppingAction);
}
