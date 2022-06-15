// Modified by Rashika Gupta
//University of Kentucky
// ------------------------------------------------------------
#include "UCNBDetectorConstruction.hh"
#include "UCNBPhysicsList.hh"
#include "UCNBPrimaryGeneratorAction.hh"
#include "UCNBPhysicsList.hh"
#include "UCNBRunAction.hh"
#include "UCNBEventAction.hh"
#include "UCNBSteppingAction.hh"
#include "UCNBStackingAction.hh"
#include "UCNBAnalysisManager.hh"
//#include "G4RunManager.hh"
#include "G4UImanager.hh"
//#include "UCNBTrackerHit.hh"
//#include"UCNBTrackerSD.hh"
//#include "FTFP_BERT.hh"
//#include "G4StepLimiterPhysics.hh"
//#include "Randomize.hh"
//#include "G4AttDefStore.hh"
//#include "G4AttDef.hh"
//#include "G4AttValue.hh"
//#ifdef G4MULTITHREADED
//#include "G4MTRunManager.hh"
//#else
#include "G4RunManager.hh"
//#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
//--------------------------------------------------------------

int main(int argc, char** argv)
{
  #ifdef G4UI_USE
    // Detect interactive mode (if no arguments) and define UI session
    //
    G4UIExecutive* ui = 0;
    if ( argc == 1 ) {
      ui = new G4UIExecutive(argc, argv);
    }
  #endif
  // Choose the Random engine

  //   CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  // Choose the Random Seed
  int seed =atoi(argv[3]);
  G4Random::setTheSeed(seed);

  // Construct the default run manager
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  // runManager->SetNumberOfThreads(4);
#else
  G4RunManager* runManager = new G4RunManager;
#endif
UCNBAnalysisManager::getInstance();UCNBAnalysisManager::getInstance();

  // ROOT filename
  if (argc == 1)
    UCNBAnalysisManager::getInstance()->ROOTfilename = "/home/scne227/newSimB/ucnb.root";
  else
    UCNBAnalysisManager::getInstance()->ROOTfilename = argv[2];



  // ROOT filename
  if (argc == 1)
    UCNBAnalysisManager::getInstance()->ROOTfilename = "/home/scne227/newSimB/ucnb.root";
  else
    UCNBAnalysisManager::getInstance()->ROOTfilename = argv[2];


 // Set mandatory initialization classes
 
  UCNBDetectorConstruction* detector = new UCNBDetectorConstruction;
  runManager->SetUserInitialization(detector);

  G4VUserPhysicsList* physicsList = new UCNBPhysicsList;
  runManager->SetUserInitialization(physicsList);
  
 // User action initialization ---missing ???????
 // runManager->SetUserInitialization(new B5ActionInitialization());

   // Set mandatory user action class

 G4VUserPrimaryGeneratorAction* gen_action = new UCNBPrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);

  runManager->SetUserAction(new UCNBRunAction);
  runManager->SetUserAction(new UCNBEventAction);
  runManager->SetUserAction(new UCNBSteppingAction);
   G4UserStackingAction* stacking_action = new UCNBStackingAction;
  runManager->SetUserAction(stacking_action);

  // Initialize G4 kernel
  //
  runManager->Initialize();
  
  // Creation of the analysis manager
//  UCNBAnalysisManager::getInstance();

 #ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
  #endif
// Get the pointer to the User Interface manager
  //
  G4UImanager * UImanager = G4UImanager::GetUIpointer();

  // batch mode

  
  if (argc!=1)
    {
      
      // execute an argument macro file if exist
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }
  // interactive mode: define UI session
  else{ 
      #ifdef G4UI_USE
      //  G4UIExecutive * ui = new G4UIExecutive(argc,argv);
    
      #ifdef G4VIS_USE
        UImanager->ApplyCommand("/control/execute init_vis.mac");    
      #else
        UImanager->ApplyCommand("/control/execute init.mac"); 
      #endif
        if (ui->IsGUI()) {
             UImanager->ApplyCommand("/control/execute gui.mac");
       }           
      ui->SessionStart();
      delete ui;
      #endif
  }

  #ifdef G4VIS_USE
    delete visManager;
  #endif
  UCNBAnalysisManager::dispose();
  delete runManager;

  return 0;
}
  // ROOT filename
  /*if (argc == 1)
    UCNBAnalysisManager::getInstance()->ROOTfilename = "/home/scne227/newSimB/ucnb.root";
  else
    UCN   
  //	  G4VModularPhysicsList* physicsList = new FTFP_BERT;
	  //  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
   //	  runManager->SetUserInitialization(physics);
  
BAnalysisManager::getInstance()->ROOTfilename = argv[2];
*/