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
  TClonesArray *branchJet = treeReader->UseBranch("FatJet");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");

  // Output root Files
  TFile* outfile = TFile::Open(Form("output_%s", inputFile), "recreate");

  // Book Canvas
  //TCanvas *c= new TCanvas ("c","Test Canvas", 800, 600);

  // Book histograms
  TH1 *elecPt = new TH1F("ElectronPt", "ElectronPt", 200, 0., 1600.);
  TH1 *elecM  = new TH1F("ElectronMass", "ElectronMass", 200, 0., 50.);

  TH1 *muPt = new TH1F("MuonPt", "MuonPt", 200, 0., 1600.);
  TH1 *muM  = new TH1F("MuonMass", "MuonMass", 200, 0., 50);

  TH1 *fatjetPt  = new TH1F("fatjetPt", "fatjetPt", 100, 0., 1600.);
  TH1 *fatjetM   = new TH1F("fatjetMass", "fatjetMass", 50, 0., 400.);
  TH1 *fatjetEta = new TH1F("fatjetEta", "fatjetEta", 100, -10., 10.);

  TH1 *missEt = new TH1F("MissingEt", "MissingEt", 100, 0., 1600);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
	// Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
                                                                     
    // If event contains at least 1 fatjet and 1 lepton
    if(branchJet->GetEntries() > 0 && ( branchMuon->GetEntries() > 0 || branchElectron->GetEntries() > 0)){
	
		TLorentzVector FJ_V, e_V, mu_V;

		// Finding leptons, jets and missing energy pt and mass distribution
        for (int entry_a = 0; entry_a < branchMuon->GetEntries(); entry_a++){
			Mu = (Muon*) branchMuon->At(entry_a);
			mu_V = Mu->P4();
			muPt->Fill(mu_V.Pt());
			muM->Fill(mu_V.M());
		}

		for (int entry_a = 0; entry_a < branchElectron->GetEntries(); entry_a++){
			Elec = (Electron*) branchElectron->At(entry_a);
			e_V = Elec->P4();
			elecPt->Fill(e_V.Pt());
			elecM->Fill(e_V.M());
		
		}
		
		for (int entry_a = 0; entry_a < branchJet->GetEntries(); entry_a++){
			fatjet = (Jet*) branchJet->At(entry_a);                         
			FJ_V = fatjet->P4();                                            
			fatjetPt -> Fill(FJ_V.Pt());                                    
			fatjetMass -> Fill(FJ_V.M());                                   
			fatjetEta -> Fill(FJ_V.Eta());                                  
								                                                                    
		}                                                                   

		 for (int entry_a = 0; entry_a < branchMissingET->GetEntries(); entry_a++){
			 MisET = (MissingET*) branchMissingET->At(entry_a);
		     missEt -> Fill(MisET->MET);
		}

	}
  }

 elecPt    -> Write();
 elecM     -> Write();
 muPt      -> Write();
 muM       -> Write();
 fatjetPt  -> Write();
 fatjetMass-> Write();
 fatjetEta -> Write();
 missEt    -> Write();

 outfile->Close();
}


void Wp_decay_output_K(){

	Wp_decay_graph_output("HVT_QQToWpToNuL2Q_3TeV.root");
	Wp_decay_graph_output("HVT_QQToWpToNuL2b_3TeV.root");
	Wp_decay_graph_output("BKG_ttWJetToLNu_LO_MLM_cut3.root");
	Wp_decay_graph_output("BKG_WZToLNu2Q_LO_MLM_cut3.root");
	Wp_decay_graph_output("BKG_WZToL3Nu_LO_MLM_cut3.root");
	Wp_decay_graph_output("BKG_WWToLNu2Q_4f_LO_MLM_cut3.root");
	Wp_decay_graph_output("BKG_WJetsToLNu_LO_MLM_cut3.root");
	Wp_decay_graph_output("BKG_ST_s-channel_4f_leptonDecays_LO_cut3.root");
	Wp_decay_graph_output("BKG_ST_t-channel_4f_inclusiveDecays_LO_cut3.root");
	Wp_decay_graph_output("BKG_WH_HToBB_WToLNu.root");
}



