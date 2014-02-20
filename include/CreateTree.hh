// Martin Goettlich @ DESY
//
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include <vector>

using namespace std;

class CreateTree
{
  private:

  TTree*              ftree;
  TString             fname;

  Bool_t              HITS;
  Bool_t              ABSORPTIONS;

  static const Int_t  MaxNum = 200000;
  static const Int_t  MaxNumPro = 1000000;

  public:

  CreateTree(TString name,Bool_t hits,Bool_t absorptions);
  ~CreateTree();

  TTree*              GetTree() const { return ftree; };
  TString             GetName() const { return fname;};
  Int_t               Fill() { return this->GetTree()->Fill(); };
  Bool_t              Write();
  void                Clear();
  static CreateTree*  Instance() { return fInstance; };
  static CreateTree*  fInstance;

  Bool_t              Hits() const { return this->HITS; };
  Bool_t              Absorptions() const { return this->ABSORPTIONS; };

  Int_t               Run;
  Int_t               Event;
  Int_t               NumOptPhotons;
  Int_t               NumCerenkovPhotons;
  Int_t               NumScintPhotons;
  Int_t               NumOptPhotonsAbsorbed;
  Int_t               NumOptPhotonsRayleigh;
  Int_t               MPPCNumHits;
  Int_t               NumBoundaryAbsorption;
  Int_t               NumBoundaryReflection;
  Int_t               NumBoundaryFresnelRefraction;
  Int_t               NumBoundaryFresnelReflection;
  Int_t               NumBoundaryLobeReflection;
  Int_t               NumBoundarySpikeReflection;
  Int_t               NumBoundaryTotalInternalReflection;
  Int_t               NumBoundaryLambertianReflection;
  Int_t               NumBoundaryBackScattering;

  Int_t               NumBoundaryStepTooSmall;
  Int_t               Process; // 1: Photo-Effect; 2: Compton-Effect

  Int_t               NumCherenkovPr;
  Int_t               NumeBrem; 

  Float_t             zPhotCompt;
  Float_t             zeIoni;
  Float_t             zScint;

  vector<float>             EProcessStart;
  vector<float>             EProcessFinal; 
  Int_t        		       NumProcess;
  vector<int>               IDProcess;
  vector<float>            DOIProcess;
  vector<float>            OptPhotonEnergy;

  Float_t             ScintillationYield;
  Float_t             RiseTime;
  Float_t             CrystalLength;
  Float_t             CrystalDiameter;
  Float_t             CrystalY;
  Float_t             CrystalX; 
  Float_t             Reflectivity;
  Float_t             AbsLength;  
  Float_t             Gap;
  Float_t             GapMaterial;
  Float_t             GapRefIndex;
  Float_t             Shape; 
  Float_t             Readout;
  Float_t             DOI;
  Float_t             ScMaterial; 

  Int_t               ReflBackside;

  Int_t               AirLayer;
  Float_t             AirGap; 
  Float_t             AirLayerSigmaAlpha; 

  Float_t             gammax;
  Float_t             gammay;
  Float_t             gammaz;

  
  
  Int_t               PartNum;

  vector<float> PartEn;
  vector<int> PartID;
  vector<int> PartProcess;
  vector<int> PartIDParent;
  vector<int> PartType;
  
  Float_t InitialPositionX;
  Float_t InitialPositionY;
  Float_t InitialPositionZ;

  Int_t		depositionCounter;
  vector<float> depositionX;
  vector<float> depositionY;
  vector<float> depositionZ;

  Int_t               TestI;
  Float_t             TestF;
  
  Float_t Total_energy[9];
  
  Float_t Total_energy_absorber;
  Float_t Total_energy_world;
  
};

/*  
 00085 enum G4OpBoundaryProcessStatus {  Undefined,
 00086                                   FresnelRefraction, FresnelReflection,
 00087                                   TotalInternalReflection,
 00088                                   LambertianReflection, LobeReflection,
 00089                                   SpikeReflection, BackScattering,
 00090                                   Absorption, Detection, NotAtBoundary,
 00091                                   SameMaterial, StepTooSmall, NoRINDEX };
*/
