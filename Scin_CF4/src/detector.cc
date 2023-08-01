#include "detector.hh"
#include "SteppingAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *ROhist)
{
	G4Track *track = step->GetTrack();
	
	//track->SetTrackStatus(fStopAndKill);
	
	/*G4StepPoint *preStepPoint = step->GetPreStepPoint();
	G4StepPoint *postStepPoint = step->GetPostStepPoint();
	
	G4ThreeVector posPhoton = preStepPoint->GetPosition();
	
	G4cout << "Photon position: " << posPhoton <<G4endl;
	
	
	
static G4ParticleDefinition* opticalphoton = G4OpticalPhoton::OpticalPhotonDefinition();
const G4ParticleDefinition* particleDef = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition();

	if(particleDef == opticalphoton)
		G4StepPoint *preStepPoint = step->GetPreStepPoint();
		G4StepPoint *postStepPoint = step->GetPostStepPoint();
		G4ThreeVector *posPhoton = preStepPoint->GetPosition();
		
		
		
		G4cout << "Photon position: " << posPhoton <<G4endl;*/
}
























