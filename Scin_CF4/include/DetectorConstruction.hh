//
// ********************************************************************
// based on examples/basic/B4/B4b
// ********************************************************************
//
// 
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "detector.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual~DetectorConstruction(); //there was a virtual before this line

  public:
    virtual G4VPhysicalVolume* Construct();
//    virtual void ConstructSDandField();

    // get methods
    //
    //const G4VPhysicalVolume* GetPMTPV() const;
    const G4VPhysicalVolume* GetCalorimeterPV() const;
    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
    
     G4LogicalVolume *GetCountingVolume1() const { return fCountingVolume1; }
     G4LogicalVolume *GetCountingVolume2() const { return fCountingVolume2; }
     G4LogicalVolume *GetCountingVolume3() const { return fCountingVolume3; }

     
  private:
    // methods
    //
    	
	
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
    
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger
     
   
    G4VPhysicalVolume*   fCalorimeterPV;      // the Calorimeter physical volume
   
    
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
    G4LogicalVolume *fScoringVolume;
    G4LogicalVolume *fCountingVolume1;
    G4LogicalVolume *fCountingVolume2;
    G4LogicalVolume *fCountingVolume3;
    
  
};
	

// inline functions


inline const G4VPhysicalVolume* DetectorConstruction::GetCalorimeterPV() const  { 
  return fCalorimeterPV; 
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

