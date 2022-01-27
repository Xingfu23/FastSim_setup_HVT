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

void Wp_decay_test(const char *inputFile)
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
  TCanvas *c= new TCanvas ("c","Test Canvas", 800, 600);

  // Book histograms
  TH1 *ePt = new TH1F("ElectronPt", "ElectronPt", 100, 0., 1600.);
  TH1 *muPt = new TH1F("MuonPt", "MuonPt", 50, 0., 200.);
  TH1 *fatjetPt = new TH1F("fatjetPt", "fatjetPt", 100, 0., 1600.);
  TH1 *fatjetM = new TH1F("fatjetMass", "fatjetMass", 100, 0., 600.);
  TH1 *missEt = new TH1F("MissingEt", "MissingEt", 100, 0., 1200);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
	// Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
                                                                     
    // If event contains at least 1 jet and 1 muon
    if(branchJet->GetEntries() > 0 && (branchMuon->GetEntries() > 0 || branchElectron->GetEntries() > 0)){
	
		TLorentzVector FJ_V, e_V;
		TLorentzVector mu_V, MisET_V;

		// Finding leptons, jets and missing energy pt and mass distribution
        for (int entry_a = 0; entry_a < branchMuon->GetEntries(); entry_a++){
			Mu = (Muon*) branchMuon->At(entry_a);
			mu_V = Mu->P4();
			muPt->Fill(mu_V.Pt());
		}

		for (int entry_a = 0; entry_a < branchElectron->GetEntries(); entry_a++){
			Elec = (Electron*) branchElectron->At(entry_a);
			e_V = Elec -> P4();
			ePt -> Fill(e_V.Pt());
		
		}

		for (int entry_a = 0; entry_a < branchJet->GetEntries(); entry_a++){
			fatjet = (Jet*) branchJet->At(entry_a);
			FJ_V = fatjet->P4();
			fatjetPt -> Fill(FJ_V.Pt());
			fatjetMass -> Fill(FJ_V.M());

		}

		for (int entry_a = 0; entry_a < branchMissingET->GetEntries(); entry_a++){
			MisET = (MissingET*) branchMissingET->At(entry_a);
			//MisET_V = MisET->P4();
            missEt -> Fill(MisET->MET);
			//missEt->Fill(MisET_V.M());
		}

    

		/*
		//Finding angle between Fatjet and muon
		for (int i=0; i<branchJet->GetEntries(); i++){
			fatJet =(Jet *) branchJet -> At(i);

			//Take the first and second muon, then calculate the value of deltaR between muons and jet
			FJ = fatJet->P4();
			for (int j=0; j<2; j++){
				mu = (Muon*) branchMuon -> At(j);
				Mu = mu->P4();
				delta_Phi = FJ.DeltaPhi(Mu);
				//cout << delta_R << endl;
				deltaPhi -> Fill(delta_Phi);
			}
		}
		*/
	}
  }


  c->Divide(2,2);
  c->cd(1);
  muPt->SetLineColor(3);
  muPt->Draw();
  c->cd(2);
  ePt->Draw();
  c->cd(3);
  missEt->Draw();

 
/*
 ePt->Write();
 muPt->Write();
 fatjetPt->Write();
 fatjetM->Write();
 missEt->Write();
 outfile->Close();
*/
}

/*
void Wp_decay_ouput(){

}
*/


