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
void Zp_delphes_output(const char *inputFile){
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
	Photontree->Branch("SubleadingElectronPt", &SubleadingElectronPt, "SubleadingElectronPt/D");
	Photontree->Branch("SubleadingElectronEta", &SubleadingElectronEta, "SubleadingElectronEta/D");
	Photontree->Branch("SubleadingElectronPhi", &SubleadingElectronPhi, "SubleadingElectronPhi/D");
	Photontree->Branch("SubleadingElectronEnergy", &SubleadingElectronEnergy, "SubleadingElectronEnergy/D");
	Photontree->Branch("LeadingMuonPt", &LeadingMuonPt, "LeadingMuonPt/D");
	Photontree->Branch("LeadingMuonEta", &LeadingMuonEta, "LeadingMuonEta/D");
	Photontree->Branch("LeadingMuonPhi", &LeadingMuonPhi, "LeadingMuonPhi/D");
	Photontree->Branch("LeadingMuonEnergy", &LeadingMuonEnergy, "LeadingMuonEnergy/D");
	Photontree->Branch("SubleadingMuonPt", &SubleadingMuonPt, "SubleadingMuonPt/D");
	Photontree->Branch("SubleadingMuonEta", &SubleadingMuonEta, "SubleadingMuonEta/D");
	Photontree->Branch("SubleadingMuonPhi", &SubleadingMuonPhi, "SubleadingMuonPhi/D");
	Photontree->Branch("SubleadingMuonEnergy", &SubleadingMuonEnergy, "SubleadingMuonEnergy/D");
	Photontree->Branch("MisEPt", &MisEPt, "MisEPt/D");
	Photontree->Branch("MisEPhi", &MisEPhi, "MisEPhi/D");
	
	vector<int> Elec1_c, Elec2_c;
	vector<int> Mu1_c, Mu2_c;
	vector<int> Pho1_c, Pho2_c;
	
	int Event_No_with1A2L = 0;
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
		Elec2_c.clear();
		Mu1_c.clear();
		Mu2_c.clear();
		Pho1_c.clear();
		Pho2_c.clear();
		
		// There are at least two leptons and one photon of each event.
		// The Pt of two same-flavour leptons must greater than 20GeV.
		// The mass of dilepton is between 70GeV and 110GeV.
		// The angular distance between photon and leptons should greater than 0.2
		if (branchPhoton->GetEntries() < 1) continue;
		if (branchMuon->GetEntries() < 2 && branchElectron->GetEntries() < 2) continue;
		Event_No_with1A2L += 1;
		
		// If the lepton type is electron
		if (branchMuon->GetEntries() == 0 && branchElectron->GetEntries() > 1){
			TLorentzVector L1, L2, a3;
			for (int entry1 = 0; entry1 < branchElectron->GetEntries(); entry1++){
				int indicator = 0;
				electron1 = (Electron*) branchElectron->At(entry1);
				if (electron1->PT < 20.) continue;
				for (int entry2 = entry1 + 1; entry2 < branchElectron->GetEntries(); entry2++){
					electron2 = (Electron*) branchElectron->At(entry2);
					if (electron2->PT < 20.) continue;
					// Checking which lepton is leading lepton.
					if (electron1->PT >= electron2->PT){
						L1 = electron1->P4();
						L2 = electron2->P4();
					}
					else{
						L1 = electron2->P4();
						L2 = electron1->P4();
					}
					if ((L1+L2).M() < 70. || (L1+L2).M() > 110.) continue;
					for (int entry3 = 0; entry3 < branchPhoton->GetEntries(); entry3++){
						photon3 = (Photon*) branchPhoton->At(entry3);
						a3 = photon3->P4();
						double DeltaR1 = a3.DeltaR(L1);
						double DeltaR2 = a3.DeltaR(L2);
						if (DeltaR1 < 0.2 || DeltaR2 < 0.2) continue;
						LeadingElectronPt        = L1.Pt();
						LeadingElectronEta       = L1.Eta();
						LeadingElectronPhi       = L1.Phi();
						LeadingElectronEnergy    = L1.E();
						SubleadingElectronPt     = L2.Pt();
						SubleadingElectronEta    = L2.Eta();
						SubleadingElectronPhi    = L2.Phi();
						SubleadingElectronEnergy = L2.E();
						LeadingMuonPt            = -1.;
						LeadingMuonEta           = -99999.;
						LeadingMuonPhi           = -99999.;
						LeadingMuonEnergy        = -1.;
						SubleadingMuonPt         = -1.;
						SubleadingMuonEta        = -99999.;
						SubleadingMuonPhi        = -99999.;
						SubleadingMuonEnergy     = -1.;
						indicator += 1;
					}
					if (indicator != 0){
						Elec1_c.push_back(entry1);
						Elec2_c.push_back(entry2);
					}
				}
			}
		}
		// If the lepton type is Muon
		else if (branchMuon->GetEntries() > 1 && branchElectron->GetEntries() == 0){
			TLorentzVector L1, L2, a3;
			for (int entry1 = 0; entry1 < branchMuon->GetEntries(); entry1++){
				int indicator = 0;
				muon1 = (Muon*) branchMuon->At(entry1);
				if (muon1->PT < 20.) continue;
				for (int entry2 = entry1 + 1; entry2 < branchMuon->GetEntries(); entry2++){
					muon2 = (Muon*) branchMuon->At(entry2);
					if (muon2->PT < 20.) continue;
					// Checking which lepton is leading lepton.
					if (muon1->PT >= muon2->PT){
						L1 = muon1->P4();
						L2 = muon2->P4();
					}
					else{
						L1 = muon2->P4();
						L2 = muon1->P4();
					}
					if ((L1+L2).M() < 70. || (L1+L2).M() > 110.) continue;
					for (int entry3 = 0; entry3 < branchPhoton->GetEntries(); entry3++){
						photon3 = (Photon*) branchPhoton->At(entry3);
						a3 = photon3->P4();
						double DeltaR1 = a3.DeltaR(L1);
						double DeltaR2 = a3.DeltaR(L2);
						if (DeltaR1 < 0.2 || DeltaR2 < 0.2) continue;
						LeadingElectronPt        = -1.;
						LeadingElectronEta       = -99999.;
						LeadingElectronPhi       = -99999.;
						LeadingElectronEnergy    = -1.;
						SubleadingElectronPt     = -1.;
						SubleadingElectronEta    = -99999.;
						SubleadingElectronPhi    = -99999.;
						SubleadingElectronEnergy = -1.;
						LeadingMuonPt            = L1.Pt();
						LeadingMuonEta           = L1.Eta();
						LeadingMuonPhi           = L1.Phi();
						LeadingMuonEnergy        = L1.E();
						SubleadingMuonPt         = L2.Pt();
						SubleadingMuonEta        = L2.Eta();
						SubleadingMuonPhi        = L2.Phi();
						SubleadingMuonEnergy     = L2.E();
						indicator += 1;
					}
					if (indicator != 0){
						Mu1_c.push_back(entry1);
						Mu2_c.push_back(entry2);
					}
				}
			}
		}
		else continue;
		// For photon part, we ask each photon's PT is greater than 25GeV
		// If there is no lepton pass selection, skip the event.
		if (Elec1_c.empty() && Mu1_c.empty()) continue;
		
		for (int entry1 = 0; entry1 < branchPhoton->GetEntries(); entry1++){
			TLorentzVector a1, a2;
			photon1 = (Photon*) branchPhoton->At(entry1);
			a1 = photon1->P4();
			if (a1.Pt() < 25.) continue;
			
			// For photon's number greater than 2, we record the first and second photon.
			if (branchPhoton->GetEntries() > 1){
				for (int entry2 = entry1 + 1; entry2 < branchPhoton->GetEntries(); entry2++){
					photon2 = (Photon*) branchPhoton->At(entry2);
					a2 = photon2->P4();
					if (a2.Pt() < 25.) continue;
					Pho1_c.push_back(entry1);
					Pho2_c.push_back(entry2);
				}
			}
			else if (branchPhoton->GetEntries() == 1){
				Pho1_c.push_back(entry1);
			}
		}
		if (Pho1_c.empty()) continue;
		
		// Event Classification and output kinematic variables.
		// Using the exsitance of element in each vector to recgonize how many photons and leptons in each event.
		TLorentzVector a1, a2, L1, L2, mET;
		// For there is only one photon in event, we record the first photon information and set second photon kinematic properties as 0.
		if (branchPhoton->GetEntries() == 1){
			photon1 = (Photon*) branchPhoton->At(Pho1_c[0]);
			a1 = photon1->P4();
			PhotonNumber = branchPhoton->GetEntries();
			LeadingPhotonPt        = a1.Pt();
			LeadingPhotonEta       = a1.Eta();
			LeadingPhotonPhi       = a1.Phi();
			LeadingPhotonEnergy    = a1.E();
			SubleadingPhotonPt     = -1.;
			SubleadingPhotonEta    = -99999.;
			SubleadingPhotonPhi    = -99999.;
			SubleadingPhotonEnergy = -1.;
			MisET = (MissingET*) branchMissingET->At(0);
			mET = MisET->P4();
			MisEPt  = mET.Pt();
			MisEPhi = mET.Phi();
			// Checking the Lepton type
			// If the leptons' type are electron
			Event_No_after_selection += 1;
		}
		else if (branchPhoton->GetEntries() > 1) {
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
	cout << "Event with 2 Leptons and 1 Photon: " << Event_No_with1A2L << endl;
	cout << "Event after event selection: " << Event_No_after_selection << endl;
	
	Photontree->Write();
	outfile->Close();
}

// Main output process
void BKG_1A2L_decay_preselection_output(){
	Zp_delphes_output("Delphes_HVT_QQToZpTo2L2gamma_MV_3000.root");
}
