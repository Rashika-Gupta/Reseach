#ifndef UCNBPhysicsList_h
#define UCNBPhysicsList_h 1
#include "G4ParticleTable.hh"
#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "G4HadronicInteraction.hh"
class G4Cerenkov;
class G4Scintillation;
class G4OpAbsorption;
class G4OpRayleigh;
class G4OpBoundaryProcess;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class UCNBPhysicsList: public G4VUserPhysicsList
{
  public:
    UCNBPhysicsList();
   ~UCNBPhysicsList();

  protected:
    // Construct particle and physics
    void ConstructParticle();
    void ConstructProcess();
 
    void SetCuts();
   // void GetHadronicInteraction() ;
    void SetMinEnergy(G4double)  ;
  protected:
    // these methods Construct particles 
    void ConstructBosons();
    void ConstructLeptons();
    void ConstructMesons();
    void ConstructBaryons();
    void ConstructIons();

  protected:
  // these methods Construct physics processes and register them
    void ConstructGeneral();
    void ConstructEM();
    void AddStepMax();
    void ConstructOp();
    void SetVerbose(G4int);
  //void ConstructHad();

  private:
    G4Cerenkov*          theCerenkovProcess;
    G4Scintillation*     theScintillationProcess;
    G4OpAbsorption*      theAbsorptionProcess;
    G4OpRayleigh*        theRayleighScatteringProcess;
    G4OpBoundaryProcess* theBoundaryProcess;
  //  G4ParticleTable::G4PTblDicIterator* theParticleIterator;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

 
