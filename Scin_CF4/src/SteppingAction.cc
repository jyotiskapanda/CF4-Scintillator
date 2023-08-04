
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

#include "G4SystemOfUnits.hh"

//=======
#include "G4ParticleDefinition.hh"
//========

#include "G4OpBoundaryProcess.hh"
#include "G4OpticalPhoton.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "detector.hh"


SteppingAction::SteppingAction(const DetectorConstruction* detectorConstruction,EventAction* EvAct)
:G4UserSteppingAction(),fDetConstruction(detectorConstruction),fEventAction(EvAct)
{ }

SteppingAction::~SteppingAction()
{ }

void SteppingAction::UserSteppingAction(const G4Step *step)//G4Step* aStep
{
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	const DetectorConstruction *detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	/*//==========================
	 if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "Scintillation")
        G4cerr << "Process: " << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
	//============================*/
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
	
	G4LogicalVolume *fCountingVolume1 = detectorConstruction->GetCountingVolume1();
	G4LogicalVolume *fCountingVolume2 = detectorConstruction->GetCountingVolume2();
	G4LogicalVolume *fCountingVolume3 = detectorConstruction->GetCountingVolume3();
	
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	if(volume == fScoringVolume){
	G4double Edep = step->GetTotalEnergyDeposit();
		
	fEventAction->AddEdep(Edep);
		
	}
	
	//=============
	static G4ParticleDefinition* opticalphoton =
            G4OpticalPhoton::OpticalPhotonDefinition();

    const G4ParticleDefinition* particleDef =
            step->GetTrack()->GetDynamicParticle()->GetParticleDefinition();
    auto poststep = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
    
    
    
    
  G4double time1;
  G4double time1C;
  G4double time2;
  G4double time3;
    //if(particleDef == opticalphoton){
        //G4cerr << "I am a photon :)" << G4endl;
        if(volume == fCountingVolume1){
        	if(particleDef == opticalphoton){
        	G4int i1 = 1;
        	if(step->GetTrack()->GetCreatorProcess()->GetProcessName() == "Scintillation"){
        	G4double time1   = step->GetTrack()->GetGlobalTime();
        	//G4cout<< "Scintillation Captured in PMT1! "<<G4endl;
        	//G4cout<< step->GetTrack()->GetCreatorProcess()->GetProcessName()  << G4endl ;
        	
        	//G4cout<< time1 <<G4endl;
        	
        	man->FillH1(0, time1);}
  
      		fEventAction->AddCount1(i1);
      		//step->GetTrack()->SetTrackStatus(fStopAndKill);
      		
      		}
        }
        if(volume == fCountingVolume2){
        	if(particleDef == opticalphoton){
        	G4int i2 = 1;
        	if(step->GetTrack()->GetCreatorProcess()->GetProcessName() == "Scintillation"){
        	G4double time2   = step->GetTrack()->GetGlobalTime();
        	//G4cout<< "Scintillation Captured in PMT2! "<<G4endl;
        	//G4cout<< step->GetTrack()->GetCreatorProcess()->GetProcessName()  << G4endl ;
        	//time2 = time;
        	man->FillH1(1, time2);}
      		fEventAction->AddCount2(i2);
      		//step->GetTrack()->SetTrackStatus(fStopAndKill);
      		}
        }
        if(volume == fCountingVolume3){
        	if(particleDef == opticalphoton){
        	G4int i3 = 1;
        	if(step->GetTrack()->GetCreatorProcess()->GetProcessName() == "Scintillation"){
        	G4double time3   = step->GetTrack()->GetGlobalTime();
        	//G4cout<< "Scintillation Captured in PMT3! "<<G4endl;
        	//G4cout<< step->GetTrack()->GetCreatorProcess()->GetProcessName()  << G4endl ;
        	//time3 = time;
        	man->FillH1(2, time3);}
      		fEventAction->AddCount3(i3);
      		//step->GetTrack()->SetTrackStatus(fStopAndKill);
      		}
        }
        }
        
    












