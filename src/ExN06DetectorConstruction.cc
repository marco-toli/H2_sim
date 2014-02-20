//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: ExN06DetectorConstruction.cc,v 1.18 2010-10-23 19:27:38 gum Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN06DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN06DetectorConstruction::ExN06DetectorConstruction()
{
  expHall_x = expHall_y = expHall_z = 0.25*m;
  
  absorber_x = absorber_y = 28.52*mm;	//20 		// just front face, back face is 30 mm
  absorber_z = 22.*cm;	//22
  
  fiber_radius = 1.*mm;
  brass_hole_radius = 1.5*mm;
  fiber_lenght = absorber_z;
  startAngle = 0.*deg;
  spanningAngle = 360.*deg;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN06DetectorConstruction::~ExN06DetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* ExN06DetectorConstruction::Construct()
{

//	------------- Materials -------------

  G4double a, z, density;
  G4int nelements;

// Air
// 
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

  G4Material* Air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  Air->AddElement(N, 70.*perCent);
  Air->AddElement(O, 30.*perCent);

// Water
// 
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);

  G4Material* Water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
  Water->AddElement(H, 2);
  Water->AddElement(O, 1);
  
// Brass
//
  G4Element* Cu = new G4Element("Copper",    "Cu", z=29., a=63.546*g/mole);
  G4Element* Zn = new G4Element("Zinc",    "Zn", z=30., a=65.409*g/mole);
  
  G4Material* Brass = new G4Material("Brass", density=8.73*g/cm3,2);
  Brass->AddElement(Cu,0.75);
  Brass->AddElement(Zn,0.25);
  
//LuAG:Ce  
//
  G4Element* Lu = new G4Element("Lutetium",  "Lu",  z=71, a=174.97*g/mole);
  G4Element* Al = new G4Element("Aluminum",  "Al",  z=27, a=28.09*g/mole);

  G4Material* LuAG = new G4Material("LuAG", density=6.7*g/cm3,3);
  LuAG->AddElement(Lu,3);
  LuAG->AddElement(Al,12);
  LuAG->AddElement(O,5);

//   const G4int NUM = 4;

//   G4double Energy[NUM]         = { 0.0001*eV, 1.0*eV, 1.84*eV, 4.08*eV };
//   G4double RIND_INDEX[NUM]     = { 4.0,4.0, 4.0, 4.0 };
//   G4double ABS_LENGTH[NUM]     = { 0.1*mm, 0.1*mm, 0.1*mm, 0.1*mm};

//   G4MaterialPropertiesTable* Si_mt = new G4MaterialPropertiesTable();
//   Si_mt->AddProperty("RINDEX",        Energy,  RIND_INDEX,     NUM);
//   Si_mt->AddProperty("ABSLENGTH",     Energy,  ABS_LENGTH,     NUM);

//   Silicon->SetMaterialPropertiesTable(Si_mt);


//
/// ------------ Generate & Add Material Properties Table ------------
//
  const G4int nEntries = 32;

  G4double PhotonEnergy[nEntries] =
            { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
              2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
              2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
              2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
              2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
              3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
              3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
              3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };
//
// Water
//	      
  G4double RefractiveIndex1[nEntries] =
            { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
              1.346,  1.3465, 1.347,  1.3475, 1.348,
              1.3485, 1.3492, 1.35,   1.3505, 1.351,
              1.3518, 1.3522, 1.3530, 1.3535, 1.354,
              1.3545, 1.355,  1.3555, 1.356,  1.3568,
              1.3572, 1.358,  1.3585, 1.359,  1.3595,
              1.36,   1.3608};

  G4double Absorption1[nEntries] =
           {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
           15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
           45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
           52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
           30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
           17.500*m, 14.500*m };

  G4double ScintilFast[nEntries] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };
  G4double ScintilSlow[nEntries] =
            { 0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,
              7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,
              3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,
              4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
              7.00, 6.00, 5.00, 4.00 };

  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();

  myMPT1->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex1,nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("ABSLENGTH",    PhotonEnergy, Absorption1,     nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("FASTCOMPONENT",PhotonEnergy, ScintilFast,     nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("SLOWCOMPONENT",PhotonEnergy, ScintilSlow,     nEntries)
        ->SetSpline(true);
  
  myMPT1->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  myMPT1->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  myMPT1->AddConstProperty("YIELDRATIO",0.8);

  const G4int NUMENTRIES_water = 60;

  G4double ENERGY_water[NUMENTRIES_water] = {
     1.56962*eV, 1.58974*eV, 1.61039*eV, 1.63157*eV,
     1.65333*eV, 1.67567*eV, 1.69863*eV, 1.72222*eV,
     1.74647*eV, 1.77142*eV, 1.7971 *eV, 1.82352*eV,
     1.85074*eV, 1.87878*eV, 1.90769*eV, 1.93749*eV,
     1.96825*eV, 1.99999*eV, 2.03278*eV, 2.06666*eV,
     2.10169*eV, 2.13793*eV, 2.17543*eV, 2.21428*eV,
     2.25454*eV, 2.29629*eV, 2.33962*eV, 2.38461*eV,
     2.43137*eV, 2.47999*eV, 2.53061*eV, 2.58333*eV,
     2.63829*eV, 2.69565*eV, 2.75555*eV, 2.81817*eV,
     2.88371*eV, 2.95237*eV, 3.02438*eV, 3.09999*eV,
     3.17948*eV, 3.26315*eV, 3.35134*eV, 3.44444*eV,
     3.54285*eV, 3.64705*eV, 3.75757*eV, 3.87499*eV,
     3.99999*eV, 4.13332*eV, 4.27585*eV, 4.42856*eV,
     4.59258*eV, 4.76922*eV, 4.95999*eV, 5.16665*eV,
     5.39129*eV, 5.63635*eV, 5.90475*eV, 6.19998*eV
  };

  //assume 100 times larger than the rayleigh scattering for now.
  G4double MIE_water[NUMENTRIES_water] = {
     167024.4*m, 158726.7*m, 150742  *m,
     143062.5*m, 135680.2*m, 128587.4*m,
     121776.3*m, 115239.5*m, 108969.5*m,
     102958.8*m, 97200.35*m, 91686.86*m,
     86411.33*m, 81366.79*m, 76546.42*m,
     71943.46*m, 67551.29*m, 63363.36*m,
     59373.25*m, 55574.61*m, 51961.24*m,
     48527.00*m, 45265.87*m, 42171.94*m,
     39239.39*m, 36462.50*m, 33835.68*m,
     31353.41*m, 29010.30*m, 26801.03*m,
     24720.42*m, 22763.36*m, 20924.88*m,
     19200.07*m, 17584.16*m, 16072.45*m,
     14660.38*m, 13343.46*m, 12117.33*m,
     10977.70*m, 9920.416*m, 8941.407*m,
     8036.711*m, 7202.470*m, 6434.927*m,
     5730.429*m, 5085.425*m, 4496.467*m,
     3960.210*m, 3473.413*m, 3032.937*m,
     2635.746*m, 2278.907*m, 1959.588*m,
     1675.064*m, 1422.710*m, 1200.004*m,
     1004.528*m, 833.9666*m, 686.1063*m
  };

  // gforward, gbackward, forward backward ratio
  G4double MIE_water_const[3]={0.99,0.99,0.8};

  myMPT1->AddProperty("MIEHG",ENERGY_water,MIE_water,NUMENTRIES_water)
        ->SetSpline(true);
  myMPT1->AddConstProperty("MIEHG_FORWARD",MIE_water_const[0]);
  myMPT1->AddConstProperty("MIEHG_BACKWARD",MIE_water_const[1]);
  myMPT1->AddConstProperty("MIEHG_FORWARD_RATIO",MIE_water_const[2]);

  Water->SetMaterialPropertiesTable(myMPT1);

  // Set the Birks Constant for the Water scintillator

  Water->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

//
// Air
//
  G4double RefractiveIndex2[nEntries] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };

  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex2, nEntries);
  
  Air->SetMaterialPropertiesTable(myMPT2);

//
///	------------- Volumes --------------

// The experimental Hall
//
  G4Box* expHall_box = new G4Box("World",expHall_x,expHall_y,expHall_z);
  G4LogicalVolume* expHall_log = new G4LogicalVolume(expHall_box,Air,"World",0,0,0);
  G4VPhysicalVolume* expHall_phys = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);

// The absorber
//
  
  
  // defining fibers position
  const int NFIBERS = 9;
  
  G4double x[NFIBERS];
  G4double y[NFIBERS];
  
  G4double spacing = 5*mm;
  
  int iY = 0, iX = 0;
  
  
  for (int iF = 0; iF < NFIBERS; iF++) {
    
      x[iF] = -5*mm + iX*spacing;
      y[iF] = 5*mm + iY*spacing;
      iX ++;
      
      if (iF == 2 || iF == 5) {
	iY--;	
	iX = 0;
      }
    
  }
  
  
      
  // solids
  G4Box* Box_abs_solid = new G4Box("Box_abs_solid",0.5*absorber_x,0.5*absorber_y,0.5*absorber_z);
  G4Tubs* Brass_hole = new G4Tubs("Brass_hole",fiber_radius, brass_hole_radius,0.5*fiber_lenght,startAngle,spanningAngle);
  G4Tubs* Crystal_fiber = new G4Tubs("Crystal_fiber",0,fiber_radius,0.5*fiber_lenght,startAngle,spanningAngle);
  
  // logical
  G4LogicalVolume* Box_abs_log = new G4LogicalVolume(Box_abs_solid, Brass, "Box_abs_log", 0,0,0);
  G4LogicalVolume* Brass_hole_log = new G4LogicalVolume(Brass_hole,Air,"Brass_hole_log",0,0,0);
  G4LogicalVolume* Crystal_fiber_log = new G4LogicalVolume(Crystal_fiber,LuAG,"Crystal_fiber_log",0,0,0);
  
  // physical: placement
  
  G4VPhysicalVolume* Box_abs_phys = new G4PVPlacement(0, G4ThreeVector(0,0,0), Box_abs_log, "Box_abs_phys", expHall_log, false, 0);
  char name[60];
  
  for (int iF = 0; iF < NFIBERS; iF++) {

    sprintf (name, "Hole_%d" , iF);
    Brass_hole_phys[iF] = new G4PVPlacement(0, G4ThreeVector(x[iF],y[iF],0), Brass_hole_log, name, Box_abs_log, false, 0);
    
    sprintf (name, "Fiber_%d" , iF);
    Crystal_phys[iF] = new G4PVPlacement(0, G4ThreeVector(x[iF],y[iF],0), Crystal_fiber_log, name, Box_abs_log, false, 0);
    
    
  }
    
  
    
    //******************************* VISUALIZATION ATTRIBUTES ******************************* //
    
//      G4Colour  white   ()              ;  // white
     G4Colour  white   (1.0, 1.0, 1.0) ;  // white
     G4Colour  gray    (0.5, 0.5, 0.5) ;  // gray
     G4Colour  black   (0.0, 0.0, 0.0) ;  // black
     G4Colour  red     (1.0, 0.0, 0.0) ;  // red
     G4Colour  green   (0.0, 1.0, 0.0) ;  // green
     G4Colour  blue    (0.0, 0.0, 1.0) ;  // blue
     G4Colour  cyan    (0.0, 1.0, 1.0) ;  // cyan
     G4Colour  magenta (1.0, 0.0, 1.0) ;  // magenta 
     G4Colour  yellow  (1.0, 1.0, 0.0) ;  // yellow
    
      	G4VisAttributes* VisAttCrystal = new G4VisAttributes(red);
	VisAttCrystal->SetVisibility(true);
// 	VisAttCrystal->SetColour(green);
  	Crystal_fiber_log->SetVisAttributes(VisAttCrystal);
	
	G4VisAttributes* VisAttHole = new G4VisAttributes(blue);
	VisAttHole->SetVisibility(true);
// 	VisAttCrystal->SetColour(green);
  	Brass_hole_log->SetVisAttributes(VisAttHole);
	
// 	Crystal_fiber_log->SetForceWireframe(true);
//   	expHall_log->SetVisAttributes(G4VisAttributes::Invisible);
	
	
    /*
    //================================================
  // Sensitive detectors : MultiFunctionalDetector
  //================================================
  //
  //  Sensitive Detector Manager.
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  //
  // Sensitive Detector Name
  G4String fiberSDname = "FiberSD";

  //------------------------
  // MultiFunctionalDetector
  //------------------------
  //
  // Define MultiFunctionalDetector with name.
  G4MultiFunctionalDetector* MFDet = new G4MultiFunctionalDetector(fiberSDname);
  SDman->AddNewDetector( MFDet );                 // Register SD to SDManager.
  Crystal_fiber_log->SetSensitiveDetector(MFDet);  // Assign SD to the logical volume.


    //------------------------
  // PS : Primitive Scorers
  //------------------------
  // Primitive Scorers are used with SDFilters according to your purpose.
  // 
  //
  //-- Primitive Scorer for Energy Deposit.
  //      Total, by protons, by electrons.
  G4String psName;
  G4PSEnergyDeposit*  scorer0 = new RE02PSEnergyDeposit(psName="totalEDep",fNx,fNy,fNz);

  //
  //------------------------------------------------------------
  //  Register primitive scorers to MultiFunctionalDetector
  //------------------------------------------------------------
  MFDet->RegisterPrimitive(scorer0);

*/
  /*
  
//	------------- Surfaces --------------
//
// Water Tank
//
  G4OpticalSurface* OpWaterSurface = new G4OpticalSurface("WaterSurface");
  OpWaterSurface->SetType(dielectric_dielectric);
  OpWaterSurface->SetFinish(ground);
  OpWaterSurface->SetModel(unified);

  new G4LogicalBorderSurface("WaterSurface",
                                 waterTank_phys,expHall_phys,OpWaterSurface);

// Air Bubble
//
  G4OpticalSurface* OpAirSurface = new G4OpticalSurface("AirSurface");
  OpAirSurface->SetType(dielectric_dielectric);
  OpAirSurface->SetFinish(polished);
  OpAirSurface->SetModel(glisur);

  G4LogicalSkinSurface* AirSurface = 
	  new G4LogicalSkinSurface("AirSurface", bubbleAir_log, OpAirSurface);

  G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>
        (AirSurface->GetSurface(bubbleAir_log)->GetSurfaceProperty());

  if (opticalSurface) opticalSurface->DumpInfo();

//
// Generate & Add Material Properties Table attached to the optical surfaces
//
  const G4int num = 2;
  G4double Ephoton[num] = {2.034*eV, 4.136*eV};

  //OpticalWaterSurface 
  G4double RefractiveIndex[num] = {1.35, 1.40};
  G4double SpecularLobe[num]    = {0.3, 0.3};
  G4double SpecularSpike[num]   = {0.2, 0.2};
  G4double Backscatter[num]     = {0.2, 0.2};

  G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();
  
  myST1->AddProperty("RINDEX",                Ephoton, RefractiveIndex, num);
  myST1->AddProperty("SPECULARLOBECONSTANT",  Ephoton, SpecularLobe,    num);
  myST1->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike,   num);
  myST1->AddProperty("BACKSCATTERCONSTANT",   Ephoton, Backscatter,     num);

  OpWaterSurface->SetMaterialPropertiesTable(myST1);

  //OpticalAirSurface
  G4double Reflectivity[num] = {0.3, 0.5};
  G4double Efficiency[num]   = {0.8, 1.0};

  G4MaterialPropertiesTable *myST2 = new G4MaterialPropertiesTable();

  myST2->AddProperty("REFLECTIVITY", Ephoton, Reflectivity, num);
  myST2->AddProperty("EFFICIENCY",   Ephoton, Efficiency,   num);

  OpAirSurface->SetMaterialPropertiesTable(myST2);
*/
//always return the physical World
  return expHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
