#ifndef UCNBAnalysisManager_h
#define UCNBAnalysisManager_h 1

//---------------------------------------------------------------------------
//
// ClassName:   UCNBAnalysisManager
//
// Description: Singleton class to hold analysis parameters and build histograms.
//           
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"

#include "globals.hh"
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//class UCNBHisto;

class UCNBAnalysisManager
{

public:
  // With description

  static UCNBAnalysisManager* getInstance();
  static void dispose();

private:

  UCNBAnalysisManager();
  ~UCNBAnalysisManager();

public: // Without description

  void bookROOT();
  void saveROOT();

  void BeginOfRun();
  void EndOfRun();

  void BeginOfEvent();
  void EndOfEvent();
  G4double timeHit1;
  void saveEventVertex(G4double, G4double, G4double, G4double, G4double,
		       G4double, G4double, G4double,G4double);

  void saveSourceVertex(G4double, G4double, G4double, G4double, G4double,
		       G4double, G4double, G4double, G4int);

  void killEventFlag(G4int);
  //  void recordStepNumber(G4int);

  void AddUpElectronOtherEnergyDeposition(G4double);
  void AddUpProtonOtherEnergyDeposition(G4double);

  void AddUpElectronSilicon1EnergyDeposition(G4double);
  void AddUpElectronSilicon2EnergyDeposition(G4double);

  void AddUpElectronDeadLayer1EnergyDeposition(G4double);
  void AddUpElectronDeadLayer2EnergyDeposition(G4double);

  void AddUpProtonSilicon1EnergyDeposition(G4double);
  void AddUpProtonSilicon2EnergyDeposition(G4double);

  void AddUpProtonDeadLayer1EnergyDeposition(G4double);
  void AddUpProtonDeadLayer2EnergyDeposition(G4double);

  void recordBremPos(G4double, G4double, G4double, G4double, G4double,G4double);
  void storePostPhoeE(G4double);

//////////////////////////


  void recordSilicon1ePosition(G4double, G4double, G4double);
  void recordSilicon2ePosition(G4double, G4double, G4double);

  void recordDead1ePosition(G4double, G4double, G4double);
  void recordDead2ePosition(G4double, G4double, G4double);

  void recordSilicon1pPosition(G4double, G4double, G4double);
  void recordSilicon2pPosition(G4double, G4double, G4double);

  void recordDead1pPosition(G4double, G4double, G4double);
  void recordDead2pPosition(G4double, G4double, G4double);

  void AddUpTotalEnergyDeposit(G4double);
  void AddUpProtonDriftTime(G4double);
  void AddUpElectronDriftTime(G4double);

  void AddUpBremsEnergyDeposit(G4double);
 
  G4int particleID;
  G4int Det1Hits;
  G4int Det2Hits;
  // electron time of flight
  G4double globalTimeHit1;
  G4double globalTimeHit2;
  G4double globalTimeDead1;
  G4double globalTimeDead2;
  G4double dEeSilicon1, dEeDead1;
   G4double dEeSilicon2, dEeDead2;
  // electron energy deposition vs. time
  G4int nTimeBin;
  G4double EdepTimeBin1[500], EdepTimeBin2[500];
  G4double EdepDeadTimeBin1[500], EdepDeadTimeBin2[500];
//---------------------------------------------------------
// Proton time of flight
  G4double globalTimeHit1P;
  G4double globalTimeHit2P;
  G4double globalTimeDead1P;
  G4double globalTimeDead2P;
// Proton energy deposition vs. time
 
  G4double EdepTimeBin1P[500], EdepTimeBin2P[500];
  G4double EdepDeadTimeBin1P[500], EdepDeadTimeBin2P[500];

  G4double pEdepTime1[500];
  G4double pEdepTime2[500];
  G4double pEdepDeadTime1[500];
  G4double pEdepDeadTime2[500];
//----------------------------------------------------
  G4String ROOTfilename;

  G4int evNo;
  G4int eStop;

  G4int HitNo1;//electron
  G4int HitNo2;
  G4int HitNo;
  G4int HitNo1d;
  G4int HitNo2d;
  
  G4int HitNo11;//proton
  G4int HitNo22;
  G4int HitNo1s;
  G4int HitNo2s;

  G4double eta;
  G4int siHit;
  G4double ePreSi;
  G4int numGamma;
  G4int numOther;
 

  Int_t dummydummy;
  Int_t dummydummy2;

  G4double dESi1Hit[100];
  G4double dESi1HitTime[100];
  G4double dESi2Hit[100];
  G4double dESi2HitTime[100];

  G4double dEDead1Hit[100];
  G4double dEDead1HitTime[100];
  G4double dEDead2Hit[100];
  G4double dEDead2HitTime[100];
  
  G4double dEDead1HitP[100];
  G4double dEDead1HitTimeP[100];
  G4double dEDead2HitP[100];
  G4double dEDead2HitTimeP[100];
 
  G4double dESi1HitP[100];
  G4double dESi1HitTimeP[100];
  G4double dESi2HitP[100];
  G4double dESi2HitTimeP[100];

  G4int PIDi[200];
  G4int trStop[200];

  G4double bremsEdep, eLossG, eLossO;
  G4int bremsIter, eSecIter, gammaIter, otherIter;
  G4int bremsID, gammaID, otherID;
  G4double bremsFill[300];
  G4double bremsCt[300];
  G4double gammaCt[200];
  G4double gammaFill[200];
  G4double otherCt[200];
  G4double otherFill[200];
  G4int hitCount;

  G4double timeFirst1, timeLast1, timeFirst2, timeLast2;
  G4double dblBck;

  G4double timeHitSi1[200];
  G4double timeHitSi2[200]; 
  G4double pixel1[200];
  G4double pixel2[200];
  G4double dESi1Tr[200];
  G4double dESi2Tr[200];

  G4double BtimeHitSi1[200];
  G4double BtimeHitSi2[200]; 
  G4double Bpixel1[200];
  G4double Bpixel2[200];
  G4double BdESi1Tr[200];
  G4double BdESi2Tr[200];

  G4double BxeSilicon1[200], ByeSilicon1[200], BzeSilicon1[200];
  G4double BxeSilicon2[200], ByeSilicon2[200], BzeSilicon2[200];
  G4int xStop[200];
  G4int  TotalNoHits;
private:

  // MEMBERS
  static UCNBAnalysisManager* fManager;

  TFile *fileROOT;
  TTree *Tout;

  // ntuple tree variables
  G4double Te0, Tp0;
  G4double Tn0, Tv0;
  G4double Tpho0;
  G4double x0, y0, z0;
  G4double pX, pY, pZ;
  G4double pXe, pYe, pZe;
  G4int PID;
  G4double thetae0, thetap0;
  G4double dEeOther;
  //G4double dEeOther,  dEeSilicon2, dEeDead1, dEeDead2;
 // G4double dEeOther, dEeSilicon1, dEeSilicon2, dEeDead1, dEeDead2;
  G4double dEpOther, dEpSilicon1, dEpSilicon2, dEpDead1, dEpDead2;
  G4double dEeSilicon1Gauss, dEeSilicon2Gauss;
  G4double dETotal;
  G4double pTOF, eTOF,etof,ptof,Etof,Ptof;
  //G4int TotalNoHits;

  G4double xeSilicon1, yeSilicon1, zeSilicon1;
  G4double xeSilicon2, yeSilicon2, zeSilicon2;

  G4double xeDead1, yeDead1, zeDead1;
  G4double xeDead2, yeDead2, zeDead2;

  G4double xpSilicon1, ypSilicon1, zpSilicon1;
  G4double xpSilicon2, ypSilicon2, zpSilicon2;

  G4double xpDead1, ypDead1, zpDead1;
  G4double xpDead2, ypDead2, zpDead2;

  G4int iKill;
  G4int iStep;
 // G4double timeHit1, timeHit2, timeDead1, timeDead2;
 G4double timeHit2, timeDead1, timeDead2;
  G4double timeHit1P, timeHit2P, timeDead1P, timeDead2P;

  G4double timeHitSi1W[200];
  G4double timeHitSi2W[200];

  G4double eEdepTime1[500];
  G4double eEdepTime2[500];

  G4double eEdepDeadTime1[500];
  G4double eEdepDeadTime2[500];

  G4int verbose;
  G4double bremsX, bremsY, bremsZ, eGInc[200];
  G4double pXpho0, pYpho0, pZpho0;
  G4double postStepEe[200];
  G4int postStepCount;
};

#endif
