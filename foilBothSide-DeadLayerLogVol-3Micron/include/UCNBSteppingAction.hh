#ifndef UCNBSteppingAction_h
#define UCNBSteppingAction_h 1
#include "G4Types.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class UCNBSteppingAction : public G4UserSteppingAction
{
  public:
    static UCNBSteppingAction* calling();
    static void dispose();
    UCNBSteppingAction();
    virtual ~UCNBSteppingAction(){};

    virtual void UserSteppingAction(const G4Step*);
    G4int Det1Counter;
G4int Det2Counter;

private:
  G4double zDecayTrap = 2.2*m;
  G4double thicknessDeadLayer = 1e-6*m; //1st tria trial with actual thickness of the detector
 //   G4double thicknessDeadLayer = 10.0e-10*m;// no thickness trial 
//G4double thicknessDeadLayer =6e-9*m; // 3rd trial 
  //  G4double thicknessDeadLayer = 0.000175*m; // 4th trial by making the thickness half that of the detector thickness
    G4double zDeadLayer = (zDecayTrap + thicknessDeadLayer);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
//if zDeadLayer = (zDecayTrap + thicknessDeadLayer)*m then on printing it gives - 1500003
//if DeadLayer = (zDecayTrap + thicknessDeadLayer) -> 1500.003 (seems like printing in mm)
//need to divide with the meter otherwise takes it as mm 
