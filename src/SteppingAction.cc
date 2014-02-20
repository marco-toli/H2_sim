#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "EventAction.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4UnitsTable.hh"
#include <iostream>
#include <fstream>
#include "CreateTree.hh"
#include "ExN06DetectorConstruction.hh"
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

using namespace std;

SteppingAction::SteppingAction()
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step * theStep)
{
//   cout << "debugging 1 " << endl;
  
  G4StepPoint* thePrePoint = theStep->GetPreStepPoint();
  G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();
  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

//   G4OpBoundaryProcessStatus boundaryStatus=Undefined;
//   static G4OpBoundaryProcess* boundary=NULL;

//   G4Track* theTrack = theStep->GetTrack();
//   G4ParticleDefinition* particleType = theTrack->GetDefinition();

//   cout << "particleType : "<< particleType << endl;
  
  // ------------------------ STORING PARTICLE AND PROCESSES ------------------------- //
  
/*

  // Printing out the processes step by step
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()!="Transportation"
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="OpAbsorption" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="phot" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="compt" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="eIoni" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="Scintillation" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="Cerenkov" 
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="OpRayleigh"
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="eBrem"
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="UserMaxStep" // !!!!!!!!!!!!!!!!!
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="msc"
     && thePostPoint->GetProcessDefinedStep()->GetProcessName()!="Rayl") 
   {
//      cout << "getting process name " << endl;
     G4cout<<thePostPoint->GetProcessDefinedStep()->GetProcessName()<<G4endl;
     
   }

   
  // Storing photoelectric and low energy processes (DOI, energy)
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="phot" 
     || thePostPoint->GetProcessDefinedStep()->GetProcessName()=="LowEnPhotoElec")
  {
//     cout << "debugging photoelectric " << endl;
    CreateTree::Instance() -> Process = 1;
    Float_t d = 0.5*CreateTree::Instance()->CrystalLength - thePostPoint->GetPosition().z();
    CreateTree::Instance() -> DOI = d;
    //CreateTree::Instance()->zPhotCompt = thePostPoint->GetPosition().z();

    CreateTree::Instance() -> EProcessStart.push_back(thePrePoint->GetTotalEnergy());
    CreateTree::Instance() -> EProcessFinal.push_back(thePostPoint->GetTotalEnergy());
    CreateTree::Instance() -> IDProcess.push_back( 1);
    CreateTree::Instance() -> DOIProcess.push_back( d);
    CreateTree::Instance() -> NumProcess++;
  }

   
  // Storing Compton processes (DOI, energy)
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="compt" 
     ||  thePostPoint->GetProcessDefinedStep()->GetProcessName()=="LowEnCompton")
  {
//     cout << "debugging compton " << endl;
    CreateTree::Instance() -> Process=2;
    Float_t d = 0.5*CreateTree::Instance()->CrystalLength - thePostPoint->GetPosition().z();
    CreateTree::Instance() -> DOI = d;
    //CreateTree::Instance()->zPhotCompt = thePostPoint->GetPosition().z();

    CreateTree::Instance()->EProcessStart.push_back(thePrePoint->GetTotalEnergy());
    CreateTree::Instance()->EProcessFinal.push_back(thePostPoint->GetTotalEnergy());
    CreateTree::Instance()->DOIProcess.push_back(d);
    CreateTree::Instance()->IDProcess.push_back( 2);
    CreateTree::Instance()->NumProcess++;
  }

  // Storing Ionization processes (DOI, energy)
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="eIoni" )
  {
//     cout << "debugging ionization " << endl;
    //CreateTree::Instance()->zeIoni = thePostPoint->GetPosition().z();
  }

  // Storing Scintillation processes
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="Scintillation" )
    
  {
//     cout << "debugging scintillation " << endl;
    //G4cout<<"Scintillation: "<<G4BestUnit(thePostPoint->GetPosition().z(),"Length")<<G4endl;
    //CreateTree::Instance()->zScint = thePostPoint->GetPosition().z();
    //G4cout<<"Mass: "<<thePrePoint->GetMass()<<G4endl;
    //if(thePrePoint->GetTotalEnergy()<0.510)
    //G4cout<<"Sc. pre point energy: "<<thePrePoint->GetTotalEnergy()<<"   post step energy: "<<thePostPoint->GetTotalEnergy()<<G4endl;
    
    G4cout<<"Scintillation: "<<G4BestUnit(theTrack->GetKineticEnergy(),"Energy")
        <<"   Name:      "<<theTrack->GetDefinition()->GetParticleName()<<"   ID: "<<theTrack->GetTrackID()
        <<"   Parent ID: "<<theTrack->GetParentID();

      if(theTrack->GetCreatorProcess())
        G4cout<<"   Creator:     "<<theTrack->GetCreatorProcess()->GetProcessName()<<G4endl;
      else G4cout<<G4endl;
    
  }

  // Storing Rayleigh processes
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="OpRayleigh" )
  {
    CreateTree::Instance()->NumOptPhotonsRayleigh++;
  }

  // Storing Cerenkov processes
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="Cerenkov" )
  {
    CreateTree::Instance()->NumCherenkovPr++;
  }
  
  // Storing Brem processes
  if(thePostPoint->GetProcessDefinedStep()->GetProcessName()=="eBrem" )
  {
    CreateTree::Instance()->NumeBrem++;
  }*/


// ------------------------ MIA PARTE ------------------------- //

	G4double energy = fabs(theStep->GetTotalEnergyDeposit())/GeV;

// 	cout << "volume: " << thePrePV->GetName() << endl;
// 	if (thePrePV->GetName() == "Fiber_4") cout << " fiber 4 small contribution = " << energy << endl;



// if (theStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()){
	if (energy > 0){

	  
 		Int_t counter = CreateTree::Instance()->depositionCounter;
         	CreateTree::Instance()->depositionCounter++;

 		G4ThreeVector pos = thePostPoint->GetPosition();
		
// 		cout << " position = " << pos[0]  << endl;
		
  		CreateTree::Instance()->depositionX.push_back(pos[0]);		
 		CreateTree::Instance()->depositionY.push_back(pos[1]);
 		CreateTree::Instance()->depositionZ.push_back(pos[2]);

		
//   		cout << " energy deposited in this step: " << energy << endl;

// 		G4double energy = fabs(theStep->GetTotalEnergyDeposit())/GeV;
// 		cout << "energy =  " << energy << endl;
// 		cout << "energy*MeV =  " << energy*GeV << endl;
		
		char name [60];
		
		for (int iF = 0; iF < 9; iF ++) {
		  sprintf (name, "Fiber_%d" , iF);
		  if (thePrePV->GetName() == name) 	  CreateTree::Instance()->Total_energy[iF] += energy;  
// 		  if (thePrePV->GetName() == "Fiber_0") cout << " fiber 4 small contribution = " << energy << endl;
		}
		
  		if (thePrePV->GetName() == "Box_abs_phys") 	  CreateTree::Instance()->Total_energy_absorber += energy;   

		CreateTree::Instance()->Total_energy_world += energy;   

 	}
 
//  }
 



// }

// ------------------------ FINE ------------------------- //
  
  

}

