
#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"



PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),fParticleGun1(0),fParticleGun2(0),fParticleGun3(0)
{
  G4int n_particle = 1;
  fParticleGun1  = new G4ParticleGun(n_particle);
  fParticleGun2  = new G4ParticleGun(n_particle);
  fParticleGun3  = new G4ParticleGun(n_particle);
  
  // default particle kinematic

  /*G4ParticleDefinition* particle
           = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(1*GeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));*/
  
  
  G4ParticleDefinition* particle1
           = G4ParticleTable::GetParticleTable()->FindParticle("proton");
  fParticleGun1->SetParticleDefinition(particle1);
  fParticleGun1->SetParticleMomentumDirection(G4ThreeVector(0. ,1. ,0.));
  fParticleGun1->SetParticleEnergy(573*keV);
  fParticleGun1->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));
  
  G4ParticleDefinition* particle2
           = G4ParticleTable::GetParticleTable()->FindParticle("triton");
  fParticleGun2->SetParticleDefinition(particle2);
  fParticleGun2->SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.));
  fParticleGun2->SetParticleEnergy(191*keV);
  fParticleGun2->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));
  
  
 //============== Muon Shower ==================
  
  
  
  G4ParticleDefinition* particle3
           = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
  fParticleGun3->SetParticleDefinition(particle3);
  fParticleGun3->SetParticleMomentumDirection(G4ThreeVector(0.8,-0.3,0.));
  fParticleGun3->SetParticleEnergy(100*GeV);
  fParticleGun3->SetParticlePosition(G4ThreeVector(0,40*cm,0));
  
  
  
  
  
  
  
  
  
  //============================================== 
  
  
  
  
  
  

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun1;
  delete fParticleGun2;
  delete fParticleGun3;
}



void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double Xpos = (2.*(G4double)G4UniformRand()-1.)*20.*cm;
  G4double Zpos = (2.*(G4double)G4UniformRand()-1.)*20.*cm;
  
  G4double xdir = (2.*(G4double)G4UniformRand()-1.);
  G4double zdir = (2.*(G4double)G4UniformRand()-1.);
 
  
 
  
 fParticleGun3->SetParticlePosition(G4ThreeVector(Xpos,1.5*m,Zpos));
 fParticleGun3->SetParticleMomentumDirection(G4ThreeVector(xdir, -2.0, zdir));
  
  //fParticleGun1->GeneratePrimaryVertex(anEvent);
  //fParticleGun2->GeneratePrimaryVertex(anEvent);
  fParticleGun3->GeneratePrimaryVertex(anEvent);
}
