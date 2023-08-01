#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(const DetectorConstruction* detectorConstruction, EventAction*);
  virtual ~SteppingAction();

  virtual void UserSteppingAction(const G4Step* step);
    
private:
  const DetectorConstruction* fDetConstruction;
  EventAction* fEventAction;
  
};

//#endif

/*class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(EventAction* eventAction);
	~SteppingAction();
	                    
	virtual void UserSteppingAction(const G4Step*);
	
private:
	const DetectorConstruction* fDetConstruction;
	EventAction *fEventAction;

};*/













#endif
