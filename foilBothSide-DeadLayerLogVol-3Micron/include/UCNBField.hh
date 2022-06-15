#ifndef UCNBField_h
#define UCNBField_h 1

#include "globals.hh"
#include "G4ElectroMagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

class UCNBField
#ifndef STANDALONE
 : public G4ElectroMagneticField
#endif

{
  
public:
  UCNBField();
  void  GetFieldValue( const  double Point[4], double *Bfield ) const;
  void LoadElectricFieldMap();
  void LoadMagneticFieldMap();
	       
  G4bool DoesFieldChangeEnergy() const {return true;}

private:
  G4double zE[1573];
  G4double rhoE[1210];
  G4double Ez[1573][1210];
  G4double Erho[1573][1210];

  G4double zB[1401];
  G4double rhoB[1146];
  G4double Bz[1401][1146];
  G4double Brho[1401][1146];
  G4double zIn[1500], rFTIn[1500], rOIn[1500];
  G4double zBin[1500],rFTBin[1500],rOBin[1500];
  G4double tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
  G4int Bct;

};

#endif
