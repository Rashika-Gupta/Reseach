#ifndef UCNBEventAction_h
#define UCNBEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "TStopwatch.h"

class G4Event;
class UCNBRunAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class UCNBEventAction : public G4UserEventAction
{
  public:
    UCNBEventAction();
   ~UCNBEventAction();
  //include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include 
  //    ${Geant4_INCLUDE_DIR})

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
    G4double getEventCPUTime();

protected:
    TStopwatch timer;

  //void AddEnergyDepositionCell(G4double de, G4double dl)
  //    {EnergyDepositionCell += de; TrackLengthCell += dl;};

  private:
    UCNBRunAction* runAct;
   
    G4double EnergyDepositionCell;
    G4double TrackLengthCell;
    G4int Det2Hits;
    G4int Det1Hits;
    G4int TotalNoHits;
    G4int Type1NoOfEvents;
    G4int Type4NoOfEvents;
protected:
};



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
