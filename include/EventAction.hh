// Martin Goettlich @ DESY
//
 
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"


class G4Event;

class EventAction : public G4UserEventAction
{
  private:

  G4int mppcCollID;

  

  public:
    EventAction();
   ~EventAction();

    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

    G4double total_energy4;
    
};


#endif

    
