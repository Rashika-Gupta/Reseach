#ifndef UCNBDetectorConstruction_h
#define UCNBDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4PVParameterised.hh"
#include "G4EqMagElectricField.hh"
#include "G4PropagatorInField.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
#include "G4ClassicalRK4.hh"

#include "UCNBField.hh"

class G4UserLimits;
class UCNBDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    UCNBDetectorConstruction();
   ~UCNBDetectorConstruction();

  public:

  G4VPhysicalVolume* Construct();

  //void SetMagField(G4double);

  private:
  G4Box*             solidWorld;
  G4LogicalVolume*   logicalWorld;
  G4VPhysicalVolume* physicalWorld;

  G4Tubs*            Silicon1;
  G4Tubs*            Mylar1;
  G4Box*             Si1Box;
  G4LogicalVolume*   logicalSilicon1;
  G4LogicalVolume*   logicalMylar1;
  G4VPhysicalVolume* physicalSilicon1;
  G4VPhysicalVolume* physicalMylar1;

  G4Tubs*            Silicon2;
  G4Tubs*            Mylar2;
  G4Box*             Si2Box;
  G4LogicalVolume*   logicalSilicon2;
  G4LogicalVolume*   logicalMylar2;
  G4VPhysicalVolume* physicalSilicon2;
  G4VPhysicalVolume* physicalMylar2;

G4Tubs* BeTube1;
G4Tubs* BeTube2;
G4LogicalVolume* logicalBeTube1;
G4LogicalVolume* logicalBeTube2;
G4VPhysicalVolume* physicalBeTube1;
G4VPhysicalVolume* physicalBeTube2;

G4Tubs* foil1;
G4Tubs* foil2;
G4LogicalVolume* logicalfoil1;
G4LogicalVolume* logicalfoil2;
G4VPhysicalVolume* physicalfoil1;
G4VPhysicalVolume* physicalfoil2;


  G4Tubs*            Backing1;
  G4LogicalVolume*   logicalBacking1;
  G4VPhysicalVolume* physicalBacking1;

  G4Tubs*            Backing2;
  G4LogicalVolume*   logicalBacking2;
  G4VPhysicalVolume* physicalBacking2;

  G4Tubs*            Dead1;
//  G4Box*             Dead1Box;
  G4LogicalVolume*   logicalDead1;
  G4VPhysicalVolume* physicalDead1;

  G4Tubs*            Dead2;
 // G4Box*             Dead2Box;
  G4LogicalVolume*   logicalDead2;
  G4VPhysicalVolume* physicalDead2;

  G4Tubs*            Drift1;
  G4LogicalVolume*   logicalDrift1;
  G4VPhysicalVolume* physicalDrift1;

  G4Tubs*            Drift2;
  G4LogicalVolume*   logicalDrift2;
  G4VPhysicalVolume* physicalDrift2;

  G4Tubs*            DecayTrap;
  G4LogicalVolume*   logicalDecayTrap;
  G4VPhysicalVolume* physicalDecayTrap;

  G4Tubs*            DecayTrapInt;
  G4LogicalVolume*   logicalDecayTrapInt;
  G4VPhysicalVolume* physicalDecayTrapInt;

  G4Tubs*            SourceHolder;
  G4LogicalVolume*   logicalSourceHolder;
  G4VPhysicalVolume* physicalSourceHolder;

  G4Tubs*            SourceRegion;
  G4LogicalVolume*   logicalSourceRegion;
  G4VPhysicalVolume* physicalSourceRegion;

  G4Tubs*            Carrier;
  G4LogicalVolume*   logicalCarrier;
  G4VPhysicalVolume* physicalCarrier;

  G4Tubs*            Brems;
  G4LogicalVolume*   logicalBrems;
  G4VPhysicalVolume* physicalBrems;

  G4Tubs*            BremE1;
  G4LogicalVolume*   logicalBremE1;
  G4VPhysicalVolume* physicalBremE1;

  G4Tubs*            BremE2;
  G4LogicalVolume*   logicalBremE2;
  G4VPhysicalVolume* physicalBremE2;

//  LEGe detector
  //G4Box*             BeTop;
  G4Tubs*             BeTop;
  G4LogicalVolume*   logicalBeTop;
  G4VPhysicalVolume* physicalBeTop;

  G4Tubs*             LEGe;
  G4LogicalVolume*   logicalLEGe;
  G4VPhysicalVolume* physicalLEGe;

  G4Tubs*             DLF;
  G4LogicalVolume*   logicalDLF;
  G4VPhysicalVolume* physicalDLF;

  G4Tubs*             DLB;
  G4LogicalVolume*   logicalDLB;
  G4VPhysicalVolume* physicalDLB;

  G4Tubs*             DLS;
  G4LogicalVolume*   logicalDLS;
  G4VPhysicalVolume* physicalDLS;
//   Ge det. West
//  G4Box*             BeTopW;
  G4Tubs*             BeTopW;
  G4LogicalVolume*   logicalBeTopW;
  G4VPhysicalVolume* physicalBeTopW;

  G4Tubs*             LEGeW;
  G4LogicalVolume*   logicalLEGeW;
  G4VPhysicalVolume* physicalLEGeW;

  G4Tubs*             DLFW;
  G4LogicalVolume*   logicalDLFW;
  G4VPhysicalVolume* physicalDLFW;

  G4Tubs*             DLBW;
  G4LogicalVolume*   logicalDLBW;
  G4VPhysicalVolume* physicalDLBW;

  G4Tubs*             DLSW;
  G4LogicalVolume*   logicalDLSW;
  G4VPhysicalVolume* physicalDLSW;
//Scinitillator Description from ScintillatorConstruction.hh file from Xua ucna code on July 23
 G4double GetScintFacePos() { return dScintFace_PosZ; };
  G4double GetWidth() { return dN2Volume_Z; };

  G4double dScintRadius;        // scintillator disc radius
  G4double dBackingRadius;      // backing veto (and overall volume) radius
  G4double dScintThick;         // scintillator disc thickness
  G4double dDeadThick;          // dead scintillator thickness (3um according to Junhua's thesis)
  G4double dBackingThick;       // backing veto thickness (M.M.'s guess)
  G4double dLightGuideThick;    // light guide thickness at scintillator edge (M.M's guess)
                                // ^^ sets scintillator to backing distance

  G4Tubs* scintOverall_shape;   // container shape for entire scintillatorConstruction

  G4LogicalVolume* container_log;       // overall container volume (filled with nitrogen)
  G4LogicalVolume* deadLayer_log;       // scintillator dead layer logical volume
  G4LogicalVolume* scintillator_log;    // actual scintillator (active region) volume
  G4LogicalVolume* lightGuide_log;      // light guide material volume
  G4LogicalVolume* backing_log;         // backing veto logical volume

 void Build(int side);         // construct only the logical container volume

  G4double dScintFace_PosZ;
  G4double dN2Volume_Z;
  G4VPhysicalVolume* deadLayer_phys;
  G4VPhysicalVolume* scintillator_phys;
  G4VPhysicalVolume* lightGuide_phys;
  G4VPhysicalVolume* backing_phys;

//-------------------------------------------------------------------------------------------
  UCNBField* Field;

  G4FieldManager *pFieldMgr;
  G4MagIntegratorStepper * pStepper;
  G4EqMagElectricField * pEquation;
  G4MagInt_Driver * pIntgrDriver;
  G4ChordFinder *pChordFinder ;
  G4PropagatorInField *propInField;

  G4UserLimits* stepLimitMyl;
  G4UserLimits* stepLimitDead;
  G4UserLimits* stepLimitCar;
};

#endif
