#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "/wk_cms2/iceeric02/local/MG5_aMC_v2_6_5/Delphes/classes/DelphesClasses.h"
#include "/wk_cms2/iceeric02/local/MG5_aMC_v2_6_5/Delphes/external/ExRootAnalysis/ExRootTreeReader.h"
#endif

//---------------------------------------------------------------------------------------------------------------------------------
void Output(const char *inputFile){
	gSystem->Load("libDelphes");
	
	// Create chain of root trees
	TChain chain("Delphes");
	chain.Add(inputFile);
	
	// Create object of class ExRootTreeReader
	ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
	Long64_t numberOfEntries = treeReader->GetEntries();
	
	// Get pointers to branches used in this analysis
	TClonesArray *branchGenParticle = treeReader->UseBranch("Particle");
	//TClonesArray *branchJet = treeReader->UseBranch("Jet");
	TClonesArray *branchElectron = treeReader->UseBranch("Electron");
	TClonesArray *branchMuon = treeReader->UseBranch("Muon");
	TClonesArray *branchPhoton = treeReader->UseBranch("Photon");
	TClonesArray *branchEvent = treeReader->UseBranch("Event");
	
	// Output root file
	TFile* outfile     = new TFile(Form("output_GenParticle_%s", inputFile), "recreate");
	TTree* Tree_Photon = new TTree("Tree_Photon", "Tree_Photon");
	
	// Output Variables
	float LeadingPhotonPT;
	float LeadingPhotonEta;
	float LeadingPhotonPhi;
	float LeadingPhotonEnergy;
	float SubLeadingPhotonPT;
	float SubLeadingPhotonEta;
	float SubLeadingPhotonPhi;
	float SubLeadingPhotonEnergy;
	float PhotonDeltaEta;
	float PhotonDeltaPhi;
	float PhotonDeltaR;
	float DiPhotonMass;
	//float DiPhotonMass_SmallDeltaR;
	float HiggsPT;
	float HiggsEta;
	//float DiPhotonMass_SmallDeltaR01_reco;
	float LeadingLeptonPT;
	float LeadingLeptonEta;
	float LeadingLeptonPhi;
	float LeadingLeptonEnergy;
	float SubLeadingLeptonPT;
	float SubLeadingLeptonEta;
	float SubLeadingLeptonPhi;
	float SubLeadingLeptonEnergy;
	float LeptonDeltaEta;
	float LeptonDeltaPhi;
	float LeptonDeltaR;
	float DiLeptonEta;
	float DiLeptonRapidity;
	float DiLeptonPT;
	
	Tree_Photon->Branch("LeadingPhotonPT", &LeadingPhotonPT, "LeadingPhotonPT/F");
	Tree_Photon->Branch("LeadingPhotonEta", &LeadingPhotonEta, "LeadingPhotonEta/F");
	Tree_Photon->Branch("LeadingPhotonPhi", &LeadingPhotonPhi, "LeadingPhotonPhi/F");
	Tree_Photon->Branch("LeadingPhotonEnergy", &LeadingPhotonEnergy, "LeadingPhotonEnergy/F");
	Tree_Photon->Branch("SubLeadingPhotonPT", &SubLeadingPhotonPT, "SubLeadingPhotonPT/F");
	Tree_Photon->Branch("SubLeadingPhotonEta", &SubLeadingPhotonEta, "SubLeadingPhotonEta/F");
	Tree_Photon->Branch("SubLeadingPhotonPhi", &SubLeadingPhotonPhi, "SubLeadingPhotonPhi/F");
	Tree_Photon->Branch("SubLeadingPhotonEnergy", &SubLeadingPhotonEnergy, "SubLeadingPhotonEnergy/F");
	Tree_Photon->Branch("PhotonDeltaEta", &PhotonDeltaEta, "PhotonDeltaEta/F");
	Tree_Photon->Branch("PhotonDeltaPhi", &PhotonDeltaPhi, "PhotonDeltaPhi/F");
	Tree_Photon->Branch("PhotonDeltaR", &PhotonDeltaR, "PhotonDeltaR/F");
	Tree_Photon->Branch("DiPhotonMass", &DiPhotonMass, "DiPhotonMass/F");
	//Tree_Photon->Branch("DiPhotonMass_SmallDeltaR", &DiPhotonMass_SmallDeltaR, "DiPhotonMass_SmallDeltaR/F");
	Tree_Photon->Branch("HiggsPT", &HiggsPT, "HiggsPT/F");
	Tree_Photon->Branch("HiggsEta", &HiggsEta, "HiggsEta/F");
	//Tree_Photon->Branch("DiPhotonMass_SmallDeltaR01_reco", &DiPhotonMass_SmallDeltaR01_reco, "DiPhotonMass_SmallDeltaR01_reco/F");
	Tree_Photon->Branch("LeadingLeptonPT", &LeadingLeptonPT, "LeadingLeptonPT/F");
	Tree_Photon->Branch("LeadingLeptonEta", &LeadingLeptonEta, "LeadingLeptonEta/F");
	Tree_Photon->Branch("LeadingLeptonPhi", &LeadingLeptonPhi, "LeadingLeptonPhi/F");
	Tree_Photon->Branch("LeadingLeptonEnergy", &LeadingLeptonEnergy, "LeadingLeptonEnergy/F");
	Tree_Photon->Branch("SubLeadingLeptonPT", &SubLeadingLeptonPT, "SubLeadingLeptonPT/F");
	Tree_Photon->Branch("SubLeadingLeptonEta", &SubLeadingLeptonEta, "SubLeadingLeptonEta/F");
	Tree_Photon->Branch("SubLeadingLeptonPhi", &SubLeadingLeptonPhi, "SubLeadingLeptonPhi/F");
	Tree_Photon->Branch("SubLeadingLeptonEnergy", &SubLeadingLeptonEnergy, "SubLeadingLeptonEnergy/F");
	Tree_Photon->Branch("LeptonDeltaEta", &LeptonDeltaEta, "LeptonDeltaEta/F");
	Tree_Photon->Branch("LeptonDeltaPhi", &LeptonDeltaPhi, "LeptonDeltaPhi/F");
	Tree_Photon->Branch("LeptonDeltaR", &LeptonDeltaR, "LeptonDeltaR/F");
	Tree_Photon->Branch("DiLeptonPT", &DiLeptonPT, "DiLeptonPT/F");
	Tree_Photon->Branch("DiLeptonEta", &DiLeptonEta, "DiLeptonEta/F");
	Tree_Photon->Branch("DiLeptonRapidity", &DiLeptonRapidity, "DiLeptonRapidity/F");
	
	// Loop over all event
	// Show up total entries
	cout << "Total Entries: " << numberOfEntries << endl;
	for(int entry = 0; entry < numberOfEntries; entry++){
		// Load selected branches with data from specified event
		treeReader->ReadEntry(entry);
		
		if (branchGenParticle->GetEntries() > 3){
			TLorentzVector a1, a2, l1, l2, h1;
			vector<int> higgs_daughter_candidate_index;
			TLorentzVector l1, l2;
			
			// Finding two the same flavour electrons and muons.
			for (int gen_entry = 0; gen_entry < branchGenParticle->GetEntries(); gen_entry++){
				GenParticle *particle1 = (GenParticle *) branchGenParticle->At(gen_entry);
				if (particle1->PID == 11 || particle1->PID == -11 || particle1->PID == 13 || particle1->PID == -13){
					for (int gen_entry2 = gen_entry + 1; gen_entry2 < branchGenParticle->GetEntries(); gen_entry2++){
						GenParticle *particle2 = (GenParticle *) branchGenParticle->At(gen_entry2);
						if (particle2->PID != -(particle1->PID)) continue;
						
					}
				}
			}
		}
	}
}


















