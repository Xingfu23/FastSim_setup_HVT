/*
root -l examples/Example1.C'("delphes_output.root")'
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iterator>

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "/wk_cms2/iceeric02/local/MG5_aMC_v2_6_5/Delphes/classes/DelphesClasses.h"
#include "/wk_cms2/iceeric02/local/MG5_aMC_v2_6_5/Delphes/external/ExRootAnalysis/ExRootTreeReader.h"
#endif

//----------------------------------------------------------------------------------------------------------------------
void Wp_delphes_output(const char *inputFile){
	gSystem->Load("libDelphes");
	
	// Create chain of root trees
	TChain chain("Delphes");
	chain.Add(inputFile);
	
	// Create object of class ExRootTreeReader
	ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
	Long64_t numberOfEntries = treeReader->GetEntries();
	
	// Get pointers to branches used in this analysis
	TClonesArray *branchMuon      = treeReader->UseBranch("Muon");
	TClonesArray *branchElectron  = treeReader->UseBranch("Electron");
	TClonesArray *branchPhoton    = treeReader->UseBranch("Photon");
	TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");
	
	// Output root Files and Book Tree
	TFile *outfile = new TFile(Form("output_%s", inputFile), "recreate");
	TTree *Photontree = new TTree("Tree_Photon", "Tree_Photon");
	
	//Setting Output Tree branch
	int    PhotonNumber;
	double LeadingPhotonPt;
	double LeadingPhotonEta;
	double LeadingPhotonPhi;
	double LeadingPhotonEnergy;
	double SubleadingPhotonPt;
	double SubleadingPhotonEta;
	double SubleadingPhotonPhi;
	double SubleadingPhotonEnergy;
	
	int    LeptonNumber;
	int    ElectronNumber;
	int    MuonNumber;
	double LeadingElectronPt;
	double LeadingElectronEta;
	double LeadingElectronPhi;
	double LeadingElectronEnergy;
	double SubleadingElectronPt;
	double SubleadingElectronEta;
	double SubleadingElectronPhi;
	double SubleadingElectronEnergy;
	double LeadingMuonPt;
	double LeadingMuonEta;
	double LeadingMuonPhi;
	double LeadingMuonEnergy;
	double SubleadingMuonPt;
	double SubleadingMuonEta;
	double SubleadingMuonPhi;
	double SubleadingMuonEnergy;
	double MisEPt;
	double MisEPhi;
	double MisEEta;
	
	Photontree->Branch("PhotonNumber", &PhotonNumber, "PhotonNumber/I");
	Photontree->Branch("LeadingPhotonPt", &LeadingPhotonPt, "LeadingPhotonPt/D");
	Photontree->Branch("LeadingPhotonEta", &LeadingPhotonEta, "LeadingPhotonEta/D");
	Photontree->Branch("LeadingPhotonPhi", &LeadingPhotonPhi, "LeadingPhotonPhi/D");
	Photontree->Branch("LeadingPhotonEnergy", &LeadingPhotonEnergy, "LeadingPhotonEnergy/D");
	Photontree->Branch("SubleadingPhotonPt", &SubleadingPhotonPt, "SubleadingPhotonPt/D");
	Photontree->Branch("SubleadingPhotonEta", &SubleadingPhotonEta, "SubleadingPhotonEta/D");
	Photontree->Branch("SubleadingPhotonPhi", &SubleadingPhotonPhi, "SubleadingPhotonPhi/D");
	Photontree->Branch("SubleadingPhotonEnergy", &SubleadingPhotonEnergy, "SubleadingPhotonEnergy/D");
	Photontree->Branch("LeptonNumber", &LeptonNumber, "LeptonNumber/I");
	Photontree->Branch("ElectronNumber", &ElectronNumber, "ElectronNumber/I");
	Photontree->Branch("MuonNumber", &MuonNumber, "MuonNumber/I");
	Photontree->Branch("LeadingElectronPt", &LeadingElectronPt, "LeadingElectronPt/D");
	Photontree->Branch("LeadingElectronEta", &LeadingElectronEta, "LeadingElectronEta/D");
	Photontree->Branch("LeadingElectronPhi", &LeadingElectronPhi, "LeadingElectronPhi/D");
	Photontree->Branch("LeadingElectronEnergy", &LeadingElectronEnergy, "LeadingElectronEnergy/D");
	//Photontree->Branch("SubleadingElectronPt", &SubleadingElectronPt, "SubleadingElectronPt/D");
	//Photontree->Branch("SubleadingElectronEta", &SubleadingElectronEta, "SubleadingElectronEta/D");
	//Photontree->Branch("SubleadingElectronPhi", &SubleadingElectronPhi, "SubleadingElectronPhi/D");
	//Photontree->Branch("SubleadingElectronEnergy", &SubleadingElectronEnergy, "SubleadingElectronEnergy/D");
	Photontree->Branch("LeadingMuonPt", &LeadingMuonPt, "LeadingMuonPt/D");
	Photontree->Branch("LeadingMuonEta", &LeadingMuonEta, "LeadingMuonEta/D");
	Photontree->Branch("LeadingMuonPhi", &LeadingMuonPhi, "LeadingMuonPhi/D");
	Photontree->Branch("LeadingMuonEnergy", &LeadingMuonEnergy, "LeadingMuonEnergy/D");
	//Photontree->Branch("SubleadingMuonPt", &SubleadingMuonPt, "SubleadingMuonPt/D");
	//Photontree->Branch("SubleadingMuonEta", &SubleadingMuonEta, "SubleadingMuonEta/D");
	//Photontree->Branch("SubleadingMuonPhi", &SubleadingMuonPhi, "SubleadingMuonPhi/D");
	//Photontree->Branch("SubleadingMuonEnergy", &SubleadingMuonEnergy, "SubleadingMuonEnergy/D");
	Photontree->Branch("MisEPt", &MisEPt, "MisEPt/D");
	Photontree->Branch("MisEPhi", &MisEPhi, "MisEPhi/D");
	Photontree->Branch("MisEEta", &MisEEta, "MisEEta/D");
	
	vector<int> Elec1_c;
	vector<int> Mu1_c;
	vector<int> Pho1_c, Pho2_c;
	
	int Event_No_with2A1L = 0;
	int Event_No_after_selection = 0;
	
	// Loop all events
	for (Int_t entry = 0; entry < numberOfEntries; ++entry){
		// Load selected branches with data from specified event
		treeReader->ReadEntry(entry);
		
		ElectronNumber = branchElectron->GetEntries();
		MuonNumber     = branchMuon->GetEntries();
		LeptonNumber   = ElectronNumber + MuonNumber;
		// Initialize the candidate vector
		Elec1_c.clear();
		Mu1_c.clear();
		Pho1_c.clear();
		Pho2_c.clear();
		
		// There are at least one leptons and two photon of each event.
		// The Pt of lepton should greater than 10 GeV.
		// The angular distance between photon and leptons should greater than 0.2
		if (PhotonNumber < 2 && LeptonNumber < 1) continue;
		Event_No_with2A1L += 1;
		
		// If the lepton type is electron
		if (branchMuon->GetEntries() == 0 && branchElectron->GetEntries() > 0){
			TLorentzVector L1, a3;
			for (int entry1 = 0; entry1 < branchElectron->GetEntries(); entry1++){
				int indicator = 0;
				electron1 = (Electron*) branchElectron->At(entry1);
				if (electron1->PT < 10.) continue;
				for (int entry3 = 0; entry3 < branchPhoton->GetEntries(); entry3++){
					photon3 = (Photon*) branchPhoton->At(entry3);
					L1 = electron1->P4();
					a3 = photon3->P4();
					double DeltaR1 = a3.DeltaR(L1);
					if (DeltaR1 < 0.2 ) continue;
					LeadingElectronPt        = L1.Pt();
					LeadingElectronEta       = L1.Eta();
					LeadingElectronPhi       = L1.Phi();
					LeadingElectronEnergy    = L1.E();
					LeadingMuonPt            = -1.;
					LeadingMuonEta           = -99999.;
					LeadingMuonPhi           = -99999.;
					LeadingMuonEnergy        = -1.;
					indicator += 1;
				}
				if (indicator != 0){
					Elec1_c.push_back(entry1);
				}
			}
		}
		// If the lepton type is Muon
		else if (branchMuon->GetEntries() > 0 && branchElectron->GetEntries() == 0){
			TLorentzVector L1, a3;
			for (int entry1 = 0; entry1 < branchMuon->GetEntries(); entry1++){
				int indicator = 0;
				muon1 = (Muon*) branchMuon->At(entry1);
				if (muon1->PT < 10.) continue;
				for (int entry3 = 0; entry3 < branchPhoton->GetEntries(); entry3++){
					photon3 = (Photon*) branchPhoton->At(entry3);
					a3 = photon3->P4();
					double DeltaR1 = a3.DeltaR(L1);
					if (DeltaR1 < 0.2) continue;
					LeadingElectronPt        = -1.;
					LeadingElectronEta       = -99999.;
					LeadingElectronPhi       = -99999.;
					LeadingElectronEnergy    = -1.;
					LeadingMuonPt            = L1.Pt();
					LeadingMuonEta           = L1.Eta();
					LeadingMuonPhi           = L1.Phi();
					LeadingMuonEnergy        = L1.E();
					indicator += 1;
				}
				if (indicator != 0){
					Mu1_c.push_back(entry1);
				}
			}
		}
		else continue;
		// For photon part, we ask that the Pt of leading photon must greater than 30 GeV
		// and the Pt of sublading photon should bigger than 20GeV. Each photon's eta value should smaller than 2.5
		// The Mass of Photon pair should be greater than 50 GeV.
		// If there is no lepton pass selection, skip the event.
		if (Elec1_c.empty() && Mu1_c.empty()) continue;
		
		for (int entry1 = 0; entry1 < branchPhoton->GetEntries(); entry1++){
			TLorentzVector a1, a2;
			photon1 = (Photon*) branchPhoton->At(entry1);
			// For photon's number greater than 2, we record the first and second photon.
			if (branchPhoton->GetEntries() > 1){
				for (int entry2 = entry1 + 1; entry2 < branchPhoton->GetEntries(); entry2++){
					photon2 = (Photon*) branchPhoton->At(entry2);
					if (photon1->PT >= photon2->PT){
						a1 = photon1->P4();
						a2 = photon2->P4();
					}
					else{
						a1 = photon2->P4();
						a2 = photon1->P4();
					}
					if (a1.Pt() < 30. || a2.Pt() < 20.) continue;
					if (a1.Eta() > 2.5 || a2.Eta() > 2.5) continue;
					if ((a1+a2).M() < 50.) continue;
					Pho1_c.push_back(entry1);
					Pho2_c.push_back(entry2);
				}
			}
		}
		if (Pho1_c.empty()) continue;
		
		// Event Classification and output kinematic variables.
		// Using the exsitance of element in each vector to recgonize how many photons and leptons in each event.
		TLorentzVector a1, a2, L1, L2, mET;
		// For there is only one photon in event, we record the first photon information and set second photon kinematic properties as 0.
		if (branchPhoton->GetEntries() > 1) {
			TLorentzVector a1_t, a2_t, a1_c, a2_c;
			// Finding photon pairs whose mass is closer to 125GeV than any other combination
			int index1 = 0;
			int index2 = 0;
			for (int a_index1 = 0; a_index1 < Pho1_c.size(); a_index1++){
				double deltaMass_c;
				double deltaMass;
				for (int a_index2 = 0; a_index2 < Pho2_c.size(); a_index2++){
					photon1_c = (Photon*) branchPhoton->At(Pho1_c[a_index1]);
					photon2_c = (Photon*) branchPhoton->At(Pho2_c[a_index2]);
					photon1_t = (Photon*) branchPhoton->At(Pho1_c[index1]);
					photon2_t = (Photon*) branchPhoton->At(Pho2_c[index2]);
					a1_t = photon1_t->P4();
					a2_t = photon2_t->P4();
					a1_c = photon1_c->P4();
					a2_c = photon2_c->P4();
					deltaMass_c = abs((a1_c + a2_c).M() - 125.);
					deltaMass   = abs((a1_t + a2_t).M() - 125.);
					if (deltaMass_c < deltaMass){
						index1 = a_index1;
						index2 = a_index2;
					}
				}
			}
			photon1 = (Photon*) branchPhoton->At(Pho1_c[index1]);
			photon2 = (Photon*) branchPhoton->At(Pho2_c[index2]);
			if (photon1->PT >= photon2->PT){
				a1 = photon1->P4();
				a2 = photon2->P4();
			}
			else{
				a1 = photon2->P4();
				a2 = photon1->P4();
			}
			PhotonNumber = branchPhoton->GetEntries();
			LeadingPhotonPt        = a1.Pt();
			LeadingPhotonEta       = a1.Eta();
			LeadingPhotonPhi       = a1.Phi();
			LeadingPhotonEnergy    = a1.E();
			SubleadingPhotonPt     = a2.Pt();
			SubleadingPhotonEta    = a2.Eta();
			SubleadingPhotonPhi    = a2.Phi();
			SubleadingPhotonEnergy = a2.E();
			MisET = (MissingET*) branchMissingET->At(0);
			mET = MisET->P4();
			MisEPt  = mET.Pt();
			MisEPhi = mET.Phi();
			MisEEta = mET.Eta();
			Event_No_after_selection += 1;
		}
		else continue;
		// Checking area
		// Checking diphoton mass
		//TLorentzVector gamma1_t, gamma2_t;
		//gamma1_t.SetPtEtaPhiE(Photon1_Pt, Photon1_Eta, Photon1_Phi, Photon1_Energy);
		//gamma2_t.SetPtEtaPhiE(Photon2_Pt, Photon2_Eta, Photon2_Phi, Photon2_Energy);
		//printf("Event Number: %d\n", entry);
		//printf("DiPhotonPt: %f\n", (gamma1_t+gamma2_t).Pt());
		
		Photontree->Fill();
	}
	cout << "Input File: " << inputFile << endl;
	cout << "Event with 1 Leptons and 2 Photon: " << Event_No_with2A1L << endl;
	cout << "Event after event selection: " << Event_No_after_selection << endl;
	
	Photontree->Write();
	outfile->Close();
}

// Main output process
void BKG_2A1L_decay_preselection_refVH_output(){
	
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_0_20.root");
	/*
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_20_50.root");
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_50_100.root");
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_100_200.root");
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_200_300.root");
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_300_500.root");
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_500_700.root");
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_700_1000.root");
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_1000_1500.root");
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_1500_2000.root");
	Wp_delphes_output("Delphes_BKG_WGToLNuG_01Jet_2000_Inf.root");
	*/
}
