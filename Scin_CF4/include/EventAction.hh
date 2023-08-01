#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"


//==============
#include "RunAction.hh"
//=============
class EventAction : public G4UserEventAction
{
  public:
    EventAction(); 
   ~EventAction();

  public:
    virtual void BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);
    
    void AddEdep(G4double Edep)     {fTotalEnergyDeposit += Edep;};      
    G4double GetEnergyDeposit()     {return fTotalEnergyDeposit;};    
        
    void AddCount1(G4int i1) {count1 += i1;}
    void AddCount2(G4int i2) {count2 += i2;}
    void AddCount3(G4int i3) {count3 += i3;}
  private:
    G4double fTotalEnergyDeposit;   // Energy deposited 
    G4int count1;
    G4int count2;
    G4int count3;
    //G4double time1;
    //G4double time2;
    //G4double time3;
};

#endif


