#include "EventAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "SteppingAction.hh"
EventAction::EventAction()
:G4UserEventAction(), fTotalEnergyDeposit(0.), count1(0), count2(0), count3(0)
{ }

EventAction::~EventAction()
{ }

void EventAction::BeginOfEventAction( const G4Event*)
{ 
 fTotalEnergyDeposit = 0.;
 count1 = 0;
 count2 = 0;
 count3 = 0;
}

void EventAction::EndOfEventAction( const G4Event*)
{   	
	//G4cout << "Energy deposition: " << fTotalEnergyDeposit << G4endl;
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	//man->FillNtupleDColumn(0, 0, fTotalEnergyDeposit); //ntuple no, col no
	
	//man->AddNtupleRow(0);
	
	//G4cout << "Scintillation count in detector 1: " << count1 << G4endl;
	//G4cout << "Scintillation count in detector 2: " << count2 << G4endl;
	//G4cout << "Scintillation count in detector 3: " << count3 << G4endl;
	
	
	
	man->FillNtupleDColumn(0, fTotalEnergyDeposit);
	man->FillNtupleIColumn(1, count1); 
	man->FillNtupleIColumn(2, count2);
	man->FillNtupleIColumn(3, count3);
	//man->FillNtupleDColumn(4, time1);
	//man->FillNtupleDColumn(5, time2);
	//man->FillNtupleDColumn(6, time3);
	
	man->AddNtupleRow(0);                       

  if(fTotalEnergyDeposit>0){
   // G4cout << fTotalEnergyDeposit/MeV << G4endl;
    man->FillH1(3, fTotalEnergyDeposit/MeV);
  }
  }


/*EventAction::EventAction(RunAction*)
{
	fEdep = 0.;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
	fEdep = 0.;
}

void EventAction::EndOfEventAction(const G4Event*)
{
	G4cout << "Energy deposition: " << fEdep << G4endl;
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->FillNtupleDColumn(0, 0, fEdep); //ntuple no, col no
	
	man->AddNtupleRow(0);
}*/







