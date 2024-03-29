// Martin Goettlich @ DESY
//
 
#include "EventAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "MyMaterials.hh"
#include "CreateTree.hh"
#include "ExN06PrimaryGeneratorAction.hh"


#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"


EventAction::EventAction()
{
	mppcCollID = -1;
}
 
EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  	G4int evtNb = evt->GetEventID();
  	if(evtNb%100 == 0 && evtNb!=0 ) 
	{
    		G4cout << "---> Begin of Event: " << evtNb << G4endl;
  	}

//   	G4SDManager * SDman = G4SDManager::GetSDMpointer();
//   	if(mppcCollID<0) 
// 	{ 
//       		mppcCollID=SDman->GetCollectionID("mppcHitCollection");
//    	}
   	
//    	G4ThreeVector InitPos[3];

  	// -------------------- INSTANCE RUN/EVENT IN TREE ---------------------- //
  	Int_t run = CreateTree::Instance() -> Run;

  	CreateTree::Instance()->Clear();
  	CreateTree::Instance()->Run = run;
  	CreateTree::Instance()->Event = evt->GetEventID();
	
	
	
	
//  	total_energy4 = 0;
	cout << "event :: " << evt->GetEventID() << endl;
	
}

void EventAction::EndOfEventAction(const G4Event* evt)
{

//   cout << "total_energy4 = " << total_energy4 << endl;
  CreateTree::Instance()->Fill();

}

