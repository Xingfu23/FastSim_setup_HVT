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
  //TCanvas *c= new TCanvas ("c","Test Canvas", 800, 600);

  // Book histograms
  TH1 *elecPt   = new TH1F("ElectronPt", "ElectronPt", 300, 0., 3000.);
  TH1 *elecMass = new TH1F("ElectronMass", "ElectronMass", 200, 0., 100.);

  TH1 *muPt   = new TH1F("MuonPt", "MuonPt", 300, 0., 3000.);
  TH1 *muMass = new TH1F("MuonMass", "MuonMass", 200, 0., 100);

  TH1 *jetPt   = new TH1F("jetPt", "jetPt", 100, 0., 1600.);
  TH1 *jetMass = new TH1F("jetMass", "jetMass", 50, 0., 400.);
  TH1 *jetEta  = new TH1F("jetEta", "jetEta", 100, -10., 10.);
  //TH1 *fatjetPt  = new TH1F("fatjetPt", "fatjetPt", 100, 0., 1600.);
  //TH1 *fatjetM   = new TH1F("fatjetMass", "fatjetMass", 50, 0., 400.);
  //TH1 *fatjetEta = new TH1F("fatjetEta", "fatjetEta", 100, -10., 10.);

  TH1 *missEt = new TH1F("MissingEt", "MissingEt", 300, 0., 3000.);

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
	
			TLorentzVector jet_V, mu_V, a_V;

			// Take 1st and 2nd Photon, reconstructing diphoton mass
			Photon *photon1, *photon2;
			
			photon1 = (Photon*) branchPhoton->At(0);
			photon2 = (Photon*) branchPhoton->At(1);

			DiPhotonMass->Fill(((photon1->P4())+(photon2->P4())).M());

			// Finding leptons, missing energy and photon pt mass and eta distribution
			for (int entry_a = 0; entry_a < branchMuon->GetEntries(); entry_a++){
				Mu = (Muon*) branchMuon->At(entry_a);
				mu_V = Mu->P4();
				muPt  ->Fill(mu_V.Pt());
				muMass->Fill(mu_V.M());
			}
		
		
			if(branchJet->GetEntries() > 0){
				for (int entry_a = 0; entry_a < branchJet->GetEntries(); entry_a++){
					jet = (Jet*) branchJet->At(entry_a);                         
					jet_V = jet->P4();                                            
					jetPt   -> Fill(jet_V.Pt());                                    
					jetMass -> Fill(jet_V.M());                                   
					jetEta  -> Fill(jet_V.Eta());                                                                                              
				}
			}

			for (int entry_a = 0; entry_a < branchMissingET->GetEntries(); entry_a++){
				MisET = (MissingET*) branchMissingET->At(entry_a);
				missEt -> Fill(MisET->MET);
			}

			for (int entry_a = 0; entry_a < branchPhoton->GetEntries(); entry_a++){
				Photon = (Photon*) branchPhoton->At(entry_a);
				a_V = Photon->P4();
				photonMass -> Fill(a_V.M());
				photonPt   -> Fill(a_V.Pt());
				photonEta  -> Fill(a_V.Eta());
			}

		}

		else if(branchMuon->GetEntries() == 0 && branchElectron->GetEntries() > 0){
	
			TLorentzVector jet_V, e_V, a_V;

			Photon *photon1, *photon2;                                
			                                                          
			photon1 = (Photon*) branchPhoton->At(0);                  
			photon2 = (Photon*) branchPhoton->At(1);                  
			                                                          
			DiPhotonMass->Fill(((photon1->P4())+(photon2->P4())).M());

			for (int entry_a = 0; entry_a < branchElectron->GetEntries(); entry_a++){ 
				Elec = (Electron*) branchElectron->At(entry_a);                       
				e_V = Elec->P4();                                                     
				elecPt  ->Fill(e_V.Pt());                                             
				elecMass->Fill(e_V.M());
			}

			if(branchJet->GetEntries() > 0){                                        
				for (int entry_a = 0; entry_a < branchJet->GetEntries(); entry_a++){
					jet = (Jet*) branchJet->At(entry_a);                            
					jet_V = jet->P4();                                              
					jetPt   -> Fill(jet_V.Pt());                                    
					jetMass -> Fill(jet_V.M());                                     
					jetEta  -> Fill(jet_V.Eta());                                   
				}                                                                   
			}
	
			for (int entry_a = 0; entry_a < branchMissingET->GetEntries(); entry_a++){
				MisET = (MissingET*) branchMissingET->At(entry_a);                    
				missEt -> Fill(MisET->MET);                                           
			}

			for (int entry_a = 0; entry_a < branchPhoton->GetEntries(); entry_a++){
				Photon = (Photon*) branchPhoton->At(entry_a);                      
				a_V = Photon->P4();                                                
				photonMass -> Fill(a_V.M());                                       
				photonPt   -> Fill(a_V.Pt());                                      
				photonEta  -> Fill(a_V.Eta());
			}                                                                       
		}
	}

  }

  elecPt       -> Write();
  elecMass     -> Write();
  muPt         -> Write();
  muMass       -> Write();
  jetPt        -> Write();
  jetMass      -> Write();
  jetEta       -> Write();
  missEt       -> Write();
  photonMass   -> Write();
  photonPt     -> Write();
  photonEta    -> Write();
  DiPhotonMass -> Write();



 outfile->Close();
}


void Wp_decay_output_K(){

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
