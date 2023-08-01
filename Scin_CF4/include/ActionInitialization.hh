
#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
///

class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(DetectorConstruction*);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    DetectorConstruction* fDetConstruction;
};

#endif

/*class ActionInitialization : public G4VUserActionInitialization
{
public:
	ActionInitialization();
	~ActionInitialization();
	
	virtual void Build() const;

};

#endif */


    
