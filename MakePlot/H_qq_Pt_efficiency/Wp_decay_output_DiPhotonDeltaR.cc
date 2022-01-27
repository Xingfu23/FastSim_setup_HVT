/*
root -l examples/Example1.C'("delphes_output.root")' 
*/
#include <iostream>
#include <vector>
#include <cmath>

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "/wk_cms2/iceeric02/local/MG5_aMC_v2_6_5/Delphes/classes/DelphesClasses.h"
#include "/wk_cms2/iceeric02/local/MG5_aMC_v2_6_5/Delphes/external/ExRootAnalysis/ExRootTreeReader.h"
#endif

//------------------------------------------------------------------------------

void Wp_decay_graph_output(const char *inputFile)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  //TClonesArray *branchJet = treeReader->UseBranch("FatJet");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");
  TClonesArray *branchPhoton = treeReader->UseBranch("Photon");

  // Output root Files
  TFile* outfile = TFile::Open(Form("output_deltaR_%s", inputFile), "recreate");

  double DeltaR_Photons, DeltaPhi_Photons, DeltaEta_Photons;
  int Total_Entries, Selected_Entries;

  // Book Tree
  TTree *Photontree = new TTree("Photontree", "Photontree");

  //Setting branch
  //Photontree->Branch("DiPhotonMass", &DiPhotonMass, "DiPhotonMass/D");
  //Photontree->Branch("DiPhotonPt", &DiPhotonPt, "DiPhotonPt/D");
  //Photontree->Branch("LeptonPt", &LeptonPt, "LeptonPt/D");
  Photontree->Branch("Selected_Entries", &Selected_Entries, "Selected_Entries/I");
  Photontree->Branch("DeltaR_Photons", &DeltaR_Photons, "DeltaR_Photons/D");
  Photontree->Branch("DeltaPhi_Photons", &DeltaPhi_Photons, "DeltaPhi_Photons/D");
  Photontree->Branch("DeltaEta_Photons", &DeltaEta_Photons, "DeltaEta_Photons/D");

  //Book histogram
  TH1 *DeltaR_DiPhoton_O   = new TH1F("DeltaR_DiPhoton", "DeltaR_DiPhoton", 100, 0., 20.);
  //TH1 *DeltaPhi_DiPhoton_O = new TH1F("DeltaPhi_DiPhoton", "DeltaPhi_DiPhoton", 100, -3.2, 3.2);
  //TH1 *DeltaEta_DiPhoton_O = new TH1F("DeltaEta_DiPhoton", "DeltaEta_DiPhoton", 100, 0., 10.);

  Total_Entries = numberOfEntries;
  cout << "Total_Entries: " << Total_Entries << endl;
  // Loop over all events
  int count = 0;
  for(Int_t entry = 0; entry < numberOfEntries; ++entry) {
	// Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

	// If events have at least 2 photon and 1 lepton.
	if(branchPhoton->GetEntries()>1){
		if(branchMuon->GetEntries() == 0 && branchElectron->GetEntries() == 0) continue;
		TLorentzVector a1, a2;

		photon1 = (Photon*) branchPhoton->At(0);
		photon2 = (Photon*) branchPhoton->At(1);
		a1 = photon1->P4();                     
		a2 = photon2->P4();
		count += 1;
		
		//DeltaR_Photons = a1.DeltaR(a2);
		//double dphi = abs(a1.Phi()-a2.Phi());
		//double deta = abs(a1.Eta()-a2.Eta());
		//double DeltaR_Photons = sqrt(pow(dphi, 2)+pow(deta, 2));
		DeltaR_Photons     = a2.DeltaR(a1);
		DeltaPhi_Photons   = a2.DeltaPhi(a1);
		DeltaEta_Photons = abs(a1.Eta()-a2.Eta());

		DeltaR_DiPhoton_O   -> Fill(DeltaR_Photons);
		//DeltaPhi_DiPhoton_O -> Fill(DeltaPhi_Photons);
		//DeltaEta_DiPhoton_O -> Fill(DeltaEta_DiPhotons);
		Photontree->Fill();
	}
  }

 Selected_Entries = count;
 cout << "Selected_Entries: " << Selected_Entries << endl;
 Photontree->Write();
 DeltaR_DiPhoton->Write();
 outfile->Close();
}

// Main output process
void Wp_decay_output_DiPhotonDeltaR(){
	
	Wp_decay_graph_output("HVT_QQToWpToNuL2gamma_Wprime_1.0TeV_2.root");     
	cout << "output done" << endl; 
	Wp_decay_graph_output("HVT_QQToWpToNuL2gamma_Wprime_1.5TeV_2.root");     
	cout << "output done" << endl; 
	Wp_decay_graph_output("HVT_QQToWpToNuL2gamma_Wprime_2.0TeV_2.root");     
	cout << "output done" << endl; 
	Wp_decay_graph_output("HVT_QQToWpToNuL2gamma_Wprime_2.5TeV_2.root");     
	cout << "output done" << endl; 
	Wp_decay_graph_output("HVT_QQToWpToNuL2gamma_Wprime_3.0TeV_2.root");     
	cout << "output done" << endl; 
	Wp_decay_graph_output("HVT_QQToWpToNuL2gamma_Wprime_3.5TeV_2.root");     
	cout << "output done" << endl; 
	Wp_decay_graph_output("HVT_QQToWpToNuL2gamma_Wprime_4.0TeV_2.root");     
	cout << "output done" << endl;
	Wp_decay_graph_output("HVT_QQToWpToNuL2gamma_Wprime_4.5TeV_2.root");     
	cout << "output done" << endl;
	Wp_decay_graph_output("HVT_QQToWpToNuL2gamma_Wprime_5.0TeV_2.root");     
	cout << "output done" << endl;



	cout << "process end" << endl;
}
