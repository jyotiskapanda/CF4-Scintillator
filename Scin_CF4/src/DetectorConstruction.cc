//
// ********************************************************************
// based on examples/basic/B4/B4b
// ********************************************************************
//
// 
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4SubtractionSolid.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

#include "G4VSolid.hh"
#include "G4OpticalSurface.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"





DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  nistManager->FindOrBuildMaterial("G4_AIR");
  nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  nistManager->FindOrBuildMaterial("G4_GLASS_PLATE");
  //https://gitlab.cern.ch/geant4/geant4/-/blob/8a51e0bc408e73c60512e61fbc51c2be9c22904d/examples/advanced/Rich/src/RichTbMaterial.cc

  G4double a,z,density, temperature, pressure;
  G4String name,symbol;
  G4int numel,natoms; 

  a=12.01*g/mole;
  G4Element* elC = new G4Element(name="Carbon", symbol="C",z=6.,a);
  a=18.998*g/mole;
  G4Element* elF = new G4Element(name="Fluorine",symbol="F",z=9.,a); 

  density=0.003884/2*g/cm3;
  temperature=298.*kelvin;
  pressure=1.0/2*atmosphere;
  a=88.01*g/mole;
 
  G4Material* CF4 =new G4Material(name="CF4",density,numel=2,kStateGas,temperature,pressure);
  CF4->AddElement(elC,natoms=1);
  CF4->AddElement(elF,natoms=4);
  
  // ------------ Generate & Add Material Properties Table ------------
  G4double hc = h_Planck*c_light;
  //
  std::vector<G4double> photonEnergy = {
    
    hc/800*nm, hc/750*nm, hc/700*nm, hc/650*nm, hc/600*nm, hc/550*nm, hc/500*nm, hc/450*nm, hc/400*nm, hc/350*nm, hc/300*nm, hc/250*nm, hc/200*nm
  };

  std::vector<G4double> refractiveIndex1 = {
        1.000480, 1.000480, 1.000480, 1.0004805, 1.000481, 1.000482, 1.000485, 1.000488, 1.000490, 1.000495, 1.000498, 1.000510, 1.000525 
  };
  std::vector<G4double> absorption = {
    10.0 * m,  10.0 * m,  10.0 * m,  10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m
  }; 
  
  /*The absorption depth is a useful parameter which gives the distance into the material at which the light drops to about 36% of its original intensity, or alternately has dropped by a factor of 1/e. Since high energy light (short wavelength), such as blue light, has a large absorption coefficient, it is absorbed in a short distance (for silicon solar cells within a few microns) of the surface, while red light (lower energy, longer wavelength) is absorbed less strongly. Even after a few hundred microns, not all red light is absorbed in silicon. The variation in the absorption depth for "blue" and "red" photons is shown below.*/

  // Material properties can be added as arrays. However, in this case it is
  // up to the user to make sure both arrays have the same number of elements.
  
 
  std::vector<G4double> scintilFast = {
    
    0.00, 0.00, 0.10, 0.18, 0.10, 0.05, 0.00, 0.00, 0.05, 0.10, 0.28, 0.20, 0.00
    
  }; //Source: A. Morozov et. al., Photon yield for ultraviolet and visible emission from cf4 excited with particles. Nuclear Instruments and Methods in Physics Research Section B: Beam Interactions with Materials and Atoms, 268(9):1456–1459, 2010

  
  //std::vector<G4double> scintilSlow = {
    //50.0, 50.0, 50.0, 50.0
  //}; //Not needed here because the decay is monoexponential.

  G4MaterialPropertiesTable* myScin = new G4MaterialPropertiesTable();

  
  // Adding a property from two std::vectors. Argument createNewKey is false
  // and spline is true.
  myScin->AddProperty("RINDEX", photonEnergy, refractiveIndex1, 13);
  myScin->AddProperty("ABSLENGTH", photonEnergy, absorption, false, true);

  // Adding a property using a C-style array.
  // Spline interpolation isn't used for scintillation.
  // Arguments spline and createNewKey both take default value false.
  myScin->AddProperty("SCINTILLATIONCOMPONENT1", photonEnergy, scintilFast, false, false);

  //myScin->AddProperty("SCINTILLATIONCOMPONENT2", photonEnergy, scintilSlow, false, true);//Monoexponential, not needed.
  myScin->AddConstProperty("SCINTILLATIONYIELD", 2700. / MeV);
  myScin->AddConstProperty("RESOLUTIONSCALE", 1.0);
  myScin->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 8.5*ns);//Source: Liu et. al., Primary scintillation characteristics of ar+cf4 gas mixtures excited by proton and alpha particles. Nuclear Instruments and Methods in Physics Research Section A: Accelerators, Spectrometers, Detectors and Associated Equipment, 694:157–161, 2012
  myScin->AddConstProperty("SCINTILLATIONRISETIME1", 1.0*ns);
  myScin->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
  myScin->AddConstProperty("SCINTILLATIONYIELD2", 0.0);
  
  //myScin->DumpTable();

  CF4->SetMaterialPropertiesTable(myScin);
  
  
  
   // Air
  //
  std::vector<G4double> refractiveIndex2 = {
    1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00
  };
  //
  std::vector<G4double> absorption2 = {
    10.0 * m,  10.0 * m,  10.0 * m,  10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m
  };
  
  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", photonEnergy, refractiveIndex2, 13);
  myMPT2->AddProperty("ABSLENGTH", photonEnergy, absorption2, 13);
  
  
  // Window Glass
  //
  std::vector<G4double> refractiveIndex3 = {
    1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5
  };
  //
  std::vector<G4double> absorption3 = {
    10.0 * m,  10.0 * m,  10.0 * m,  10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m, 10.0 * m
  };
  

  G4MaterialPropertiesTable* myMPT3 = new G4MaterialPropertiesTable();
  myMPT3->AddProperty("RINDEX", photonEnergy, refractiveIndex3, 13);
  myMPT3->AddProperty("ABSLENGTH", photonEnergy, absorption3, 13);
  
  
  

 
    
  //Volume of the box
  G4double calorSizeZ = 20.*cm;
  G4double calorSizeXY  = 20.*cm;

  auto worldSizeXY = 10. * calorSizeXY;
  auto worldSizeZ  = 10. * calorSizeZ; 

  auto defaultMaterial = G4Material::GetMaterial("G4_AIR");
  //auto wallMat= G4Material::GetMaterial("G4_AIR");
  auto wallMat= G4Material::GetMaterial("G4_STAINLESS-STEEL");
  auto WinMat = G4Material::GetMaterial("G4_GLASS_PLATE");


  defaultMaterial->SetMaterialPropertiesTable(myMPT2);
  
  WinMat->SetMaterialPropertiesTable(myMPT3);
  
  
  //wallMat->SetMaterialPropertiesTable(myMPT5);
  
  

  //     
  // World
  //
  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeXY/2, worldSizeXY/2, worldSizeZ/2); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0);     

  //                               
  // Calorimeter
  //  
  auto calorimeterS
    = new G4Box("Calorimeter",     // its name
                 calorSizeXY/2, calorSizeXY/2, calorSizeZ/2); // its size
                         
  auto calorLV
    = new G4LogicalVolume(
                 calorimeterS,     // its solid
                 CF4,    // its material
                 "Calorimeter");   // its name
                 //testMat,    // its material
                 
  fScoringVolume = calorLV;
                                   
  fCalorimeterPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 calorLV,          // its logical volume                         
                 "Calorimeter",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0);
   
   
   
   
                      
  //PMT
    
  
  G4double WinRadius = 4.7*cm; 
  G4double WinLength = 1.*cm; 

  


  G4double PMTRadius = 4.6*cm; 
  G4double PMTLength = 12.7*cm; 
  G4ThreeVector positionPMT1 = G4ThreeVector(0,0,-calorSizeZ/2 - PMTLength/2 - WinLength/2);
  G4ThreeVector positionPMT2 = G4ThreeVector(calorSizeZ/2 + PMTLength/2 + WinLength/2,0,0);//WinLength/2
  G4ThreeVector positionPMT3 = G4ThreeVector(0,0,calorSizeZ/2 + PMTLength/2 + WinLength/2);
//  G4double PMTwindowradius = 46.*cm; // minimal window size

  G4Tubs* PMT1
    = new G4Tubs("PMT1", 0.,PMTRadius/2,PMTLength/2,0.*deg,360.*deg);

  G4LogicalVolume* PMT1LV
    = new G4LogicalVolume(
                 PMT1,               // its solid
                 defaultMaterial,    // its material
                 "PMT1");             // its name
                 
  fCountingVolume1 = PMT1LV;

  auto fPMT1PV = new G4PVPlacement(0,               // no rotation
                    positionPMT1,  // at (x,y,z)
                    PMT1LV,    // its logical volume
                    "PMT1",        // its name
                    worldLV,         // its mother volume
                    false,           // no boolean operations
                    0,               // copy number
                    true); // checking overlaps
  
  //Rotation matrix for PMT2
  G4ThreeVector u = G4ThreeVector(0,0,1);
  G4ThreeVector v = G4ThreeVector(1,0,0);
  G4ThreeVector w = G4ThreeVector(0,1,0);
  G4RotationMatrix rotM  = G4RotationMatrix(u,w,v);
  G4Transform3D transform = G4Transform3D(rotM, positionPMT2);
 
  
  G4Tubs* PMT2
    = new G4Tubs("PMT2", 0.,PMTRadius/2,PMTLength/2,0.*deg,360.*deg);

  G4LogicalVolume* PMT2LV
    = new G4LogicalVolume(
                 PMT2,               // its solid
                 defaultMaterial,    // its material
                 "PMT2");             // its name
                 
  fCountingVolume2 = PMT2LV;

 auto fPMT2PV = new G4PVPlacement(transform,               // no rotation
                    //positionPMT2,  // at (x,y,z)
                    PMT2LV,    // its logical volume
                    "PMT2",        // its name
                    worldLV,         // its mother volume
                    false,           // no boolean operations
                    0,               // copy number
                    true); // checking overlaps
                    
   G4Tubs* PMT3
    = new G4Tubs("PMT3", 0.,PMTRadius/2,PMTLength/2,0.*deg,360.*deg);
    
   G4LogicalVolume* PMT3LV
    = new G4LogicalVolume(
                 PMT3,               // its solid
                 defaultMaterial,    // its material
                 "PMT3");             // its name
                 
                 
   fCountingVolume3 = PMT3LV;

 auto fPMT3PV = new G4PVPlacement(0,               // no rotation
                    positionPMT3,  // at (x,y,z)
                    PMT3LV,    // its logical volume
                    "PMT3",        // its name
                    worldLV,         // its mother volume
                    false,           // no boolean operations
                    0,               // copy number
                    true); // checking overlaps
                    
    
    
    
     
     
                    
  //===================================Glass Windows==================================
  

   
  G4ThreeVector positionWin1 = G4ThreeVector(0,0,-calorSizeZ/2);
  G4ThreeVector positionWin2 = G4ThreeVector(calorSizeZ/2 ,0,0);
  G4ThreeVector positionWin3 = G4ThreeVector(0,0,calorSizeZ/2);


  G4Tubs* Win1
    = new G4Tubs("Win1", 0.,WinRadius/2,WinLength/2,0.*deg,360.*deg);
    
    
    

  G4LogicalVolume* Win1LV
    = new G4LogicalVolume(
                 Win1,               // its solid
                 WinMat,    // its material
                 "Win1");             // its name
                 

  auto fWin1PV = new G4PVPlacement(0,               // no rotation
                    positionWin1,  // at (x,y,z)
                    Win1LV,    // its logical volume
                    "Win1",        // its name
                    worldLV,         // its mother volume
                    false,           // no boolean operations
                    0,               // copy number
                    true); // checking overlaps
  
  //Rotation matrix
  
  G4RotationMatrix rotM1  = G4RotationMatrix(u,w,v);
  G4Transform3D transform1 = G4Transform3D(rotM1, positionWin2);
 
  
  G4Tubs* Win2
    = new G4Tubs("Win2", 0.,WinRadius/2,WinLength/2,0.*deg,360.*deg);

  G4LogicalVolume* Win2LV
    = new G4LogicalVolume(
                 Win2,               // its solid
                 WinMat,    // its material
                 "Win2");             // its name
                 

 auto fWin2PV = new G4PVPlacement(transform1,               // no rotation
                    //positionPMT2,  // at (x,y,z)
                    Win2LV,    // its logical volume
                    "Win2",        // its name
                    worldLV,         // its mother volume
                    false,           // no boolean operations
                    0,               // copy number
                    true); // checking overlaps
                    
   G4Tubs* Win3
    = new G4Tubs("Win3", 0.,WinRadius/2,WinLength/2,0.*deg,360.*deg);
    
   G4LogicalVolume* Win3LV
    = new G4LogicalVolume(
                 Win3,               // its solid
                 WinMat,    // its material
                 "Win3");             // its name
                 
                 

 auto fWin3PV = new G4PVPlacement(0,               // no rotation
                    positionWin3,  // at (x,y,z)
                    Win3LV,    // its logical volume
                    "Win3",        // its name
                    worldLV,         // its mother volume
                    false,           // no boolean operations
                    0,               // copy number
                    true); // checking overlaps

  
  
  
  
   
   //====================== Reflective Wrapping =============================
   

   G4OpticalSurface* OpSurface = new G4OpticalSurface("reflector");
   
   G4LogicalBorderSurface* Surface = new
G4LogicalBorderSurface("reflector", fCalorimeterPV, worldPV,OpSurface);
   OpSurface -> SetType(dielectric_metal);
   OpSurface -> SetModel(glisur);

   
   
  
   G4MaterialPropertiesTable *OpSurfaceProperty = new G4MaterialPropertiesTable();
   
   
   std::vector<G4double> reflectivity = {

   0.868, 0.875, 0.880, 0.907, 0.910, 0.913, 0.918, 0.919, 0.920, 0.921, 0.922, 0.926, 0.930
  
  };//https://laserbeamproducts.wordpress.com/2014/06/19/reflectivity-of-aluminium-uv-visible-and-infrared/      (For pure uncoated Aluminum)
  
  std::vector<G4double> efficiency = {
    1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1. ,1.
  };
   
   OpSurfaceProperty -> AddProperty("REFLECTIVITY",photonEnergy,reflectivity,13);
   OpSurfaceProperty -> AddProperty("EFFICIENCY",photonEnergy,efficiency,13);
   OpSurface -> SetMaterialPropertiesTable(OpSurfaceProperty);
   
   
   
   
   //=======================================================================
   
   
   
   
  
  
  

  return worldPV;
}




































