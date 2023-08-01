#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

/*RunAction::RunAction()
 : G4UserRunAction()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("root");
  analysisManager->SetVerboseLevel(1);  
  analysisManager->SetFirstHistoId(1);
    
  // Creating histograms
  //
  analysisManager->CreateH1("1","energy (MeV) deposited",1000,0.,2.);
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run*)
{
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();

  
   // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "testem4";
  analysisManager->OpenFile(fileName);    
}

void RunAction::EndOfRunAction(const G4Run*)
{  
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();         

  //save histograms      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
  */
  RunAction::RunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();	
	
	
	man->CreateNtuple("Scoring", "Scoring");
	man->CreateNtupleDColumn("fEdep");
	man->CreateNtupleIColumn("PMT1");
	man->CreateNtupleIColumn("PMT2");
	man->CreateNtupleIColumn("PMT3");
	//man->CreateNtupleDColumn("time1");
	//man->CreateNtupleDColumn("time2");
	//man->CreateNtupleDColumn("time3");
	man->FinishNtuple(0);
	
	
	man->CreateH1("0","Time in PMT1",50,0.,50.);
	man->CreateH1("1","Time in PMT2",50,0.,50.);
	man->CreateH1("2","Time in PMT3",50,0.,50.);
	man->CreateH1("3","Non Zero Energy Deposited in Chamber",100,0.0,0.20);
	
	
}


RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* run)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();  //included in g4root
	
	G4int runID = run->GetRunID();
	
	std::stringstream strRunID;
	strRunID << runID;
	
	man->OpenFile("output"+strRunID.str()+".root");
	
	
}

void RunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();  //IMPORTANT!
	
	man->CloseFile();
  
  
  
  
  
  
  
  
  
  
  
  
  
}