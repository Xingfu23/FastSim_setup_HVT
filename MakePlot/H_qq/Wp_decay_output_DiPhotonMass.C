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
  TFile* outfile = TFile::Open(Form("output_%s", inputFile), "recreate");

  // Book Canvas

  // Book histograms
  TH1 *photonPt   = new TH1F("PhotonPt", "PhotonPt", 300, 0., 3000.);
  TH1 *photonMass = new TH1F("PhotonMass", "PhotonMass", 300, 0., 3000.);
  TH1 *photonEta  = new TH1F("PhotonEta", "PhotonEta", 100, -10., 10.);
  TH1 *DiPhotonMass = new TH1F("DiPhotonMass", "DiPhotonMass", 100, 0., 200.);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
	// Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
                                                                     
    // If event contains at least 1 lepton
	if(branchPhoton->GetEntries()>1){
		if(branchMuon->GetEntries() > 0 && branchElectron->GetEntries() == 0){
	
			// TLorentzVector;

			// Take first and second photon
			Photon *photon1 *photon2;

			photon1 = (Photon*) branchPhoton->At(0);
			photon2 = (Photon*) branchPhoton->At(1);

			// Plot their invarinat mass
			DiPhotonMass->Fill(((photon1->P4())+(photon2->P4())).M());
		}
		else if(branchMuon->GetEntries() == 0 && branchElectron->GetEntries() > 0){
		
		
		
		}
	}
  }	

 DiPhotonMass->Write();
 outfile->Close();
}


void Wp_decay_output_DiPhotonMass(){

	Wp_decay_graph_output("BKG_DiphotonJets_Loosefilter.root");
	cout << "output done" << endl;
	//Wp_decay_graph_output("BKG_DiphotonJets_Test.root");
	//cout << "output done" << endl;
	//Wp_decay_graph_output("BKG_DiphotonJets_Tighterfilter.root");
	//cout << "output done" << endl;
	//Wp_decay_graph_output("BKG_GJets_HeavyFilter.root");
	//cout << "output done" << endl;
	//Wp_decay_graph_output("HVT_QQToWpToNuL2gamma_3TeV.root");
	cout << "output done" << endl;
	cout << "process end" << endl;
}
