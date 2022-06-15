#include "UCNBEventAction.hh"
#include "UCNBAnalysisManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "TStopwatch.h"
#include "UCNBSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
UCNBEventAction::UCNBEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
UCNBEventAction::~UCNBEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void UCNBEventAction::BeginOfEventAction(const G4Event*)
{
 // G4cout<<"Begin of event action ===== EA"<<G4endl;
  // analysis
  UCNBAnalysisManager::getInstance()->BeginOfEvent();
  UCNBAnalysisManager::getInstance()->HitNo1=0;
  UCNBAnalysisManager::getInstance()->HitNo2=0;
  UCNBAnalysisManager::getInstance()->Det1Hits=0.;
  UCNBAnalysisManager::getInstance()->Det2Hits=0.;
  UCNBAnalysisManager::getInstance()->timeHit1 = 0.;
  timer.Reset();
  timer.Start();
}

G4double UCNBEventAction::getEventCPUTime() {
  timer.Stop();
  G4double time = timer.CpuTime();
  timer.Continue();
  return time;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void UCNBEventAction::EndOfEventAction(const G4Event* evt)
{
  timer.Stop();
  //G4int TotalNoHits =  UCNBAnalysisManager::getInstance()->Det1Hits + UCNBAnalysisManager::getInstance()->Det2Hits;
 /* G4cout << "Total number of hits "<<UCNBAnalysisManager::getInstance()->TotalNoHits<<G4endl;
  if(UCNBAnalysisManager::getInstance()->TotalNoHits == 2){
    Type1NoOfEvents++;
    G4cout<<"Type 1 hit the detector 1 and 2 just once "<<G4endl;
     
  }
  else if(UCNBAnalysisManager::getInstance()->TotalNoHits == 3){
    Type4NoOfEvents++;
   
    G4cout<<"Has hit the detector 1/2 2 more than once ++++++++ "<<G4endl;

  }
  G4cout<<"Type1NoOfEvents "<<Type1NoOfEvents<<G4endl;
  G4cout<<"Type4NoOfEvents "<<Type4NoOfEvents<<G4endl;
  *///G4cout<<"Time hits detector 1(timeHit1) ln 63 EA+++++++++"<<UCNBAnalysisManager::getInstance()->globalTimeHit1<<G4endl;
  // analysis
  UCNBAnalysisManager::getInstance()->EndOfEvent();
  G4int event_id = evt->GetEventID();

  //G4cout<<"End of event action ===== EA"<<G4endl;
  // get number of stored trajectories
    //}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
