#include "UCNBPrimaryGeneratorAction.hh"
#include "UCNBDetectorConstruction.hh"
#include "UCNBAnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"
#include "G4Proton.hh"
#include "G4VEmModel.hh"
 #include "globals.hh"

UCNBPrimaryGeneratorAction::UCNBPrimaryGeneratorAction(UCNBDetectorConstruction* myDC)
  :UCNBDetector(myDC)
{
}

UCNBPrimaryGeneratorAction::~UCNBPrimaryGeneratorAction()
{
  delete particleGun;
}

void UCNBPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 // G4cout<<" Generating primaries    :PGA"<<G4endl;

  // Electron-Proton Event Generator

  G4double MN = 939.565379*1e6; // eV
  G4double MP = 938.272046*1e6; // eV
  G4double ME = 510.998928*1e3; // eV

  G4double MNk = 939565.379*keV; // keV
  G4double MPk = 938272.046*keV; // keV
  G4double MEk = 510.998928*keV; // keV

  G4double elambda = -1.2701;
  G4double alpha = 1./137.036;

  G4double POL = 1.0;
//--------------------------------------------------------
  G4double MN1 = MN/ME;
  G4double MP1 = MP/ME;
  G4double ME1 = 1.;
  //--------------------------------------------------------
  G4double DELTA = MN1 - MP1;
  G4double XCRIT = 0.5*(DELTA + ME1*ME1/DELTA);
  G4double EEMAX = DELTA - (DELTA*DELTA-1.)/(2.*MN1);

  G4double A = -2.*elambda*(1.+elambda)/(1.+3.*elambda*elambda);
  G4double B = -2.*elambda*(1.-elambda)/(1.+3.*elambda*elambda);
  G4double ALIT = (1.-elambda*elambda)/(1.+3.*elambda*elambda);
  G4double el1 = elambda;
  G4double BLIT = 0.0;
  //--------------------------------------------------------
  G4double gg = 1.08;
  G4double ff = 0.00;
  G4double EE, PE,THETAE, PHIE;

  while (gg>ff) {
    EE = ENERGY2() + 1.;
    PE = sqrt(EE*EE-1.);
    THETAE = M_PI*G4UniformRand();
    PHIE = 2.*M_PI*G4UniformRand();
    ff = aprob2(A,el1,THETAE,EE);
    gg = 1.08*G4UniformRand();
  }
  
  G4double EU = cos(PHIE)*sin(THETAE);
  G4double EV = sin(PHIE)*sin(THETAE);
  G4double EW = cos(THETAE);

  G4double THETAEP = 1.;
  G4double THETAMAX = 0.;
  G4double THETAP, PHIP, PU, PV, PW;

 tryAgain:
   THETAP = M_PI*G4UniformRand();
  //THETAP = acos(2.*G4UniformRand()-1);

  if ( std::abs(THETAP - M_PI/2.) < 0.0001 ) {
    if (THETAP > M_PI/2.) {THETAP = THETAP + 0.001;}
    else {THETAP = THETAP - 0.001;}
  }

  PHIP = 2.*M_PI*G4UniformRand();
  PU = cos(PHIP)*sin(THETAP);
  PV = sin(PHIP)*sin(THETAP);
  PW = cos(THETAP);

//  Cosine of Angle between proton and electron direction
  THETAEP = EU*PU+PV*EV+EW*PW;

 Double_t Sfm = (MN1/MP1)*(EEMAX-EE)/PE; // Maximum Cosine(theta_ep)

  if (EE >= XCRIT) {
    THETAMAX = -1.0*sqrt(1.-Sfm*Sfm);
    if (THETAEP>THETAMAX) goto tryAgain;
  }

  G4double XM = MN1 - EE;
  G4double X = XM*XM-PE*PE+MP1*MP1;
  G4double Y = PE*THETAEP;

  G4double aa = 4.*(XM*XM-Y*Y);
  G4double bb = 4.*Y*X;
  G4double hbig = 0.5*(MP1+MN1+1./(MP1+MN1));
  G4double hlit = 4.*(MN1*MN1-MP1*MP1)*(EE-XCRIT)*(hbig-EE);
  G4double ss = sqrt(bb*bb - 4.*aa*hlit);

  G4double PPP = (-bb + ss)/(2.*aa);
  G4double PPM = (-bb - ss)/(2.*aa);

  G4double RRP = sqrt(PPP*PPP+MP1*MP1);
  G4double RRM = sqrt(PPM*PPM+MP1*MP1);

  G4double EPMAX = sqrt((PE+(MN1*(DELTA-EE)/(MN1-EE-PE)))*
			(PE+(MN1*(DELTA-EE)/(MN1-EE-PE))) + MP1*MP1);

  G4double EPMIN;
  if (EE < XCRIT) {
    EPMIN = sqrt(((MN1*(DELTA-EE)/(MN1-EE-PE))-PE)*
                 ((MN1*(DELTA-EE)/(MN1-EE-PE))-PE) + MP1*MP1);
  }
  else {
    EPMIN = sqrt((PE-(MN1*(DELTA-EE)/(MN1-EE-PE)))*
                 (PE-(MN1*(DELTA-EE)/(MN1-EE-PE))) + MP1*MP1);
  }

  G4int jblah2, jblah3;
  if (EE>XCRIT) {
    if (RRP<EPMAX && RRP>EPMIN) jblah2 = 1;
    if (RRM<EPMAX && RRM>EPMIN) jblah3 = 1;
  }

  G4double FDP = std::abs(PPP/RRP + (PPP+Y)/(MN1-EE-RRP));
  G4double FDM = std::abs(PPM/RRM + (PPM+Y)/(MN1-EE-RRM));

  G4double E1P = sqrt(PPP*PPP + PE*PE + 2.*PE*PPP*THETAEP);
  G4double E1M = sqrt(PPM*PPM + PE*PE + 2.*PE*PPM*THETAEP);

  G4double CHI1 =  ( 1. - ALIT*(PE*PE+Y*PPP)/(EE*E1P) + BLIT/EE 
		     + POL*(A*PE/EE*EW-B*(PE*EW+PPP*PW)/E1P))
    * EE*PE*PPP*PPP*sin(THETAP)*sin(THETAE);

  G4double CHI2 = ( 1. - ALIT*(PE*PE+Y*PPM)/(EE*E1M) + BLIT/EE
		    + POL*(A*PE/EE*EW-B*(PE*EW+PPM*PW)/E1M))
    * EE*PE*PPM*PPM*sin(THETAP)*sin(THETAE);

  G4double DIFFP = 1.;
  G4double DIFFM = 1.;

  G4double H, F1, F2, EP, PP;
  if (EE >= XCRIT) {
    H = G4UniformRand();
    F1 = (CHI1*DIFFP/FDP)/(CHI1*DIFFP/FDP + CHI2*DIFFM/FDM);
    F2 = (CHI2*DIFFM/FDM)/(CHI1*DIFFP/FDP + CHI2*DIFFM/FDM);
    if (H > F2) {EP = RRP; PP = PPP;}
    else {EP = RRM; PP = PPM;}
  }
  else if (EE < XCRIT) {
    EP = RRP; PP = PPP; CHI2 = 0.;
  }
  if ( (EP > EPMAX) || (EP<EPMIN) ) goto tryAgain;

  G4double BETA = PE/EE;
  G4double BETAR = std::abs(BETA-(1.-BETA*BETA)*PP/EP*THETAEP);
  G4double gam = 0.5772;

  G4double FERMI = 1. + alpha*M_PI/BETAR + alpha*alpha*
    (11./4.- gam - log(2.*BETAR*EE*(0.01)/4.) + M_PI*M_PI/(3.*BETAR*BETAR));

  G4double DGAMMA1 = FERMI*(CHI1*DIFFP/FDP+CHI2*DIFFM/FDM);

  G4double REJECT;
  if (EE > XCRIT) {REJECT = 5000.;}
  else if (EE <= XCRIT) {REJECT = 5000.;}
  G4double G = REJECT*G4UniformRand();

  if (G > DGAMMA1) goto tryAgain;

  G4double EN = MN1 - EE - EP;
  G4double NU = -1.*(PE*EU+PP*PU)/EN;
  G4double NV = -1.*(PE*EV+PP*PV)/EN;
  G4double NW = -1.*(PE*EW+PP*PW)/EN;
  G4double THETANE = EU*NU+EV*NV+EW*NW;

  // Electron variables
  G4double Te0 = (EE-1.0) * ME/1000*keV;
  G4double px_hat_e = EU;
  G4double py_hat_e = EV;
  G4double pz_hat_e = EW;
  G4double thetaElectron = acos(pz_hat_e);
  // Proton variables
  G4double Tp0 = (EP*ME - MP)/1000*keV;
  G4double px_hat_p = PU;
  G4double py_hat_p = PV;
  G4double pz_hat_p = PW;
  G4double thetaProton   = acos(pz_hat_p);
  // Neutrino variable
  G4double Tv0 = (EN * ME /1000) * keV;
  G4double Tn0 = (Tv0 + Tp0 + Te0) + (MEk + MPk - MNk); // masses in eV

  // Sample vertex position
   G4double x_vertex, y_vertex, z_vertex;
   G4double x_test, y_test;
   G4double testRadius = 1.e99;
   while (testRadius > 0.05) {
    x_test = (-0.05 + G4UniformRand()*2.*0.05)*m;
    y_test = (-0.05 + G4UniformRand()*2.*0.05)*m;
    testRadius = sqrt(x_test*x_test + y_test*y_test);
  }
  x_vertex = x_test*m;
  y_vertex = y_test*m;
  z_vertex = (-1.5 + G4UniformRand()*3.0)*m;
  
  // Generate electron and proton
  G4int n_particle = 1;
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  particleGun = new G4ParticleGun(n_particle);
  G4ParticleDefinition* particle1 = particleTable->FindParticle("e-");
  particleGun->SetParticleDefinition(particle1);
  particleGun->SetParticleEnergy(Te0);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(px_hat_e,py_hat_e,pz_hat_e));

  particleGun->SetParticlePosition(G4ThreeVector(x_vertex,y_vertex,z_vertex));
  particleGun->GeneratePrimaryVertex(anEvent);

 // particleGun = new G4ParticleGun(n_particle);
//  G4ParticleDefinition* particle2 = particleTable->FindParticle("proton");
//  particleGun->SetParticleDefinition(particle2);
//  particleGun->SetParticleEnergy(Tp0);
//  particleGun->SetParticleMomentumDirection(G4ThreeVector(px_hat_p,py_hat_p,pz_hat_p));
//  particleGun->SetParticlePosition(G4ThreeVector(x_vertex,y_vertex,z_vertex));
//  particleGun->GeneratePrimaryVertex(anEvent);


  // Save initial vertex variables
  UCNBAnalysisManager::getInstance()->saveEventVertex(Te0/keV, Tp0/keV,
						      px_hat_e,py_hat_e,pz_hat_e, thetaElectron, thetaProton, Tn0/keV, Tv0/keV);
  //proton variables
 // UCNBAnalysisManager::getInstance()->saveSourceVertex(Te0/keV, Tp0/keV,x_vertex/m, y_vertex/m, z_vertex/m, px_hat_p, py_hat_p,pz_hat_p,Tv0/keV);
  //
  // G4cout<<"Te0=="<<Te0<<G4endl;
}

double UCNBPrimaryGeneratorAction::ENERGY2(){
  while( 1 ) {
    G4double E0 = 2.5295196;
    G4double b = 0.0;
    G4double f = 0.00;
    G4double y = 1.80;

    G4double E, FERMI;
    while (f<y) {
      E=(E0-1.0)*G4UniformRand();
      y=1.80*G4UniformRand();
      FERMI = 1.;
      f=FERMI*sqrt(E*E+2*E)*(E0-(E+1))*(E0-(E+1))*(E+1)*(1+b*1/(E+1));
    }
    return E;

  }
}

double UCNBPrimaryGeneratorAction::aprob2(double A, double lambda,
					  double theta, double E) {
  while( 1 ) {
    double beta = sqrt(E*E - 1.)/E;
    double temp = sin(theta)*(1.0+A*beta*cos(theta));
    return temp;
  }
}
