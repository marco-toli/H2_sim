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
// $Id: exampleN06.cc,v 1.18 2010-10-23 19:33:55 gum Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Description: Test of Continuous Process G4Cerenkov
//              and RestDiscrete Process G4Scintillation
//              -- Generation Cerenkov Photons --
//              -- Generation Scintillation Photons --
//              -- Transport of optical Photons --
// Version:     5.0
// Created:     1996-04-30
// Author:      Juliet Armstrong
// mail:        gum@triumf.ca
//     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "ExN06PhysicsList.hh"
#include "ExN06PrimaryGeneratorAction.hh"
#include "ExN06DetectorConstruction.hh"
#include "ExN06RunAction.hh"
#include "ExN06StackingAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "ExN06SteppingVerbose.hh"

#include "CreateTree.hh"
#include "TString.h"

#include "Randomize.hh"
#include "TRandom1.h"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

long int CreateSeed();



int main(int argc,char** argv)
{
  // Seed the random number generator manually
  //
  G4long myseed = CreateSeed();
  cout << "MySeed = " << myseed << endl;
  
  CLHEP::HepRandom::setTheSeed(myseed);
  
  CreateTree* mytree = new CreateTree("H2_sim",0,0);

  // User Verbose output class
  //
  G4VSteppingVerbose* verbosity = new ExN06SteppingVerbose;
  G4VSteppingVerbose::SetInstance(verbosity);
  
  // Run manager
  //
  G4RunManager* runManager = new G4RunManager;

  // UserInitialization classes - mandatory
  //
  G4VUserPhysicsList* physics = new ExN06PhysicsList;
  runManager-> SetUserInitialization(physics);
  //
  G4VUserPrimaryGeneratorAction* gen_action = new ExN06PrimaryGeneratorAction;
  runManager->SetUserAction(gen_action);
  //
  G4VUserDetectorConstruction* detector = new ExN06DetectorConstruction;
  runManager-> SetUserInitialization(detector);
  
#ifdef G4VIS_USE
  // visualization manager
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  // UserAction classes
  //
  G4UserRunAction* run_action = new ExN06RunAction;
  runManager->SetUserAction(run_action);
  
  //
  G4UserEventAction* event_action = new EventAction;
  runManager->SetUserAction(event_action);
  
  //
  G4UserStackingAction* stacking_action = new ExN06StackingAction;
//   runManager->SetUserAction(stacking_action);
  
  //
  SteppingAction* stepping_action = new SteppingAction;
  runManager->SetUserAction(stepping_action);
  
  // Initialize G4 kernel
  //
  runManager->Initialize();
    
  // Get the pointer to the User Interface manager
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer(); 
   
  if (argc==1)   // Define UI session for interactive mode
    {
#ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
#ifdef G4VIS_USE
                UImanager->ApplyCommand("/control/execute vis.mac");     
// 		UImanager->ApplyCommand("/control/execute gps.mac");    
#endif
      ui->SessionStart();
      delete ui;
#endif
    }
  else         // Batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }
   
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;
  delete verbosity;
  
  
  
  char filename[100] = "./sim_out.root";
  TFile* outfile = new TFile(filename,"RECREATE");
  outfile->cd();
  G4cout<<"Writing tree to file "<< filename << " ..." << G4endl;
  mytree->GetTree()->Write();
  outfile->Write();
  outfile->Close();

  return 0;
}


long int CreateSeed()
{
  	TRandom1 rangen;
  	long int s = time(0);
  	cout<<"Time : "<<s<<endl;
  	s+=getpid();
  	cout<<"PID  : "<<getpid()<<endl;
  
  	FILE * fp = fopen ("/proc/uptime", "r");
  	int uptime,upsecs;
  	if (fp != NULL)
    	{
      		char buf[BUFSIZ];
      		int res;
      		char *b = fgets (buf, BUFSIZ, fp);
      		if (b == buf)
        	{
          		/* The following sscanf must use the C locale.  */
          		setlocale (LC_NUMERIC, "C");
          		res = sscanf (buf, "%i", &upsecs);
          		setlocale (LC_NUMERIC, "");
          		if (res == 1) uptime = (time_t) upsecs;
        	}
      		fclose (fp);
    	}

  	cout<<"Uptime: "<<upsecs<<endl;
  	s+=upsecs;
  
  	cout<<"Seed for srand: "<<s<<endl;
  	srand(s);
  	rangen.SetSeed(rand());
  	long int seed = round(1000000*rangen.Uniform());
  	return seed;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
