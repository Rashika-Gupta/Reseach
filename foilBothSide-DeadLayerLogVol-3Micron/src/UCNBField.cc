	#include "UCNBField.hh"
	#include "G4SystemOfUnits.hh"
	#include <iostream>
	#include <fstream>
	#include <cmath>
//------------------------------------------------------------------------------------------------------------------------
	
	UCNBField::UCNBField() : G4ElectroMagneticField()
	{

	}

	void UCNBField::GetFieldValue(const G4double point[4], G4double *Bfield ) const
	{
   //These (x,y,z) positions are returned in units of [mm]
  G4double x_mm = point[0];
  G4double y_mm = point[1];
  G4double z_mm = point[2];

 //Convert to units of [m]
  G4double x_m = x_mm/1000.;
  G4double y_m = y_mm/1000.;
  G4double z_m = z_mm/1000.;

  // Sinusoidal interpolation of field
  G4double zgrid[6];
  zgrid[0] = -9.0;
  zgrid[1] = -2.2;
  zgrid[2] = -1.5;
  zgrid[3] =  1.5;
  zgrid[4] =  2.2;
  zgrid[5] =  9.0;

  G4double Bzgrid[6];
  Bzgrid[0] = 0.6;
  Bzgrid[1] = 0.6;
  Bzgrid[2] = 1.0;
  Bzgrid[3] = 1.0;
  Bzgrid[4] = 0.6;
  Bzgrid[5] = 0.6;
  static const double     pi  = 3.14159265358979323846;
  int zindexLow = 0;
  for (G4int i=0; i<5; i++) {
  if ( (z_m > zgrid[i]) && (z_m < zgrid[i+1]) ) zindexLow = i;
  }
  G4double base = (Bzgrid[zindexLow] + Bzgrid[zindexLow+1]) / 2.;
  G4double amp  = (Bzgrid[zindexLow] - Bzgrid[zindexLow+1]) / 2.;
  G4double dz   = zgrid[zindexLow+1] - zgrid[zindexLow];
  G4double l    = (z_m - zgrid[zindexLow])/dz; 

  G4double Bxint, Byint, Bzint, Brhoint;
  Bzint = base + amp*cos(l*pi );
  Brhoint = amp*pi *sin(l*pi )/(2.*dz);

  Bxint   = Brhoint * x_m;
  Byint   = Brhoint * y_m;
 // G4cout<<"Field  "<<G4endl;
  //Magnetic field: (x,y,z) -> (0,1,2) components of Bfield[.]
  G4double Exint = 0.;
  G4double Eyint = 0.;
  G4double Ezint = 0.;

  Bfield[0] = Bxint * tesla;
  Bfield[1] = Byint * tesla;
  Bfield[2] = Bzint * tesla;
  ///////////////////////////////////////////////////////
  Bfield[3] = Exint * kilovolt/cm;
  Bfield[4] = Eyint * kilovolt/cm;
  Bfield[5] = Ezint * kilovolt/cm;
   // Electric field: (x,y,z) -> (3,4,5) components of Bfield[.]
  
  //----------------------------------------------------------------
  /*  
   G4double deltaphiNeg =  30.; // [kV]
   G4double deltazNeg   =  70.; // [cm]
   G4double deltaphiPos =  -30.; // [kV]
   G4double deltazPos   =  70.; // [cm]
 

  // symmetric_run1:
  if ( (z_m > -2.2) && (z_m <= -1.5)) Ezint = -1.*deltaphiNeg/deltazNeg;
  if ( (z_m >= 1.5) && (z_m < 2.2 ) ) Ezint = -1.*deltaphiPos/deltazPos;

  // asymmetric_run2:
  //if ( (z_m >= -2.2) && (z_m <=-1.5) ) Ezint =(-30./.7);
  //if ( (z_m >= 1.5) && (z_m <=2.2 ) ) Ezint = (30./.7);

  // Electric field: (x,y,z) -> (3,4,5) components of Bfield[.]
  Bfield[3] = Exint * kilovolt/cm;
  Bfield[4] = Eyint * kilovolt/cm;
  Bfield[5] = Ezint * kilovolt/cm;

  //////////////////////////////////////////////////////
  
//Electric field: (x,y,z) -> (3,4,5) components of Bfield
  Bfield[3] = Exint * kilovolt/m;
  Bfield[4] = Eyint * kilovolt/m;
  Bfield[5] = Ezint * kilovolt/m;
  
  if ( (z_m > 1.5) && (z_m <= 2.2) ){  Ezint = (30./0.7); } // IN CM, DAMMIT 
  else if ( (z_m >= -2.2) && (z_m <= -1.5) ) { Ezint = (-30./0.7); } // KV/CM
  else Ezint = 0;

  Bfield[3] = Exint*volt/cm;
  Bfield[4] = Eyint*volt/cm;
  Bfield[5] = Ezint*volt/cm;
  
 ////////////////////////////////////////////////////////////////////////
  G4double Exint;//=0.0;
  G4double Eyint;//=0.0;
  G4double Ezint;//=0.0;

  G4double deltaphiNeg =  -30.; // [kV]
  G4double deltazNeg   =  10.; // [cm]
  G4double deltaphiPos = -30.; // [kV]
  G4double deltazPos   =  10.; // [cm]

 
  //G4double tiny = 1.0e-9;
  // Leave E_x/E_y=0, but in electrodes put appropriate fields.
  // Note that the field is defined for +z, so a 30./5. kV/cm field 
  // is defined with the more positive electrode at lower Z.
  if ( (z_m > 1.5) && (z_m <= 1.6) ){  Ezint = (30./0.01); } // IN CM, DAMMIT 
  else if ( (z_m >= -1.6) && (z_m <= -1.5) ) { Ezint = (-30./0.01); } // KV/CM
  else Ezint = 0;

  // Electric field: (x,y,z) -> (3,4,5) components of Bfield[.

//G4cout<<"dz="<<dz<< G4endl;
  	if (z_m > -2.3 && z_m < -1.5) {
	G4cout<< zindexLow <<"dz="<<dz<< x_m << " " << y_m << " " << z_m << " " << Bfield[0]/tesla << " " << Bfield[1]/tesla << " " << Bfield[2]/tesla << G4endl;
	}
         if (z_m >1.5 && z_m < 2.3) {
	G4cout<< zindexLow << x_m << " " << y_m << " " << z_m << " " << Bfield[0]/tesla << " " << Bfield[1]/tesla << " " << Bfield[2]/tesla << G4endl;
	}
*/
}

