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

  // Book histograms
  TH1 *ePt = new TH1F("ElectronPt", "ElectronPt", 400, 0., 1600.);
  TH1 *muPt = new TH1F("MuonPt", "MuonPt", 400, 0., 1600.);
  TH1 *eM = new TH1F("ElectronMass", "ElectronMass", 100, 0., 500.);
  TH1 *muM = new TH1F("MuonMass", "MuonMass", 100, 0., 500.);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
	// Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
                                                                     
    // If event contains at least 2 jet and 1 muon
    if(branchJet->GetEntries() > 1 && branchMuon->GetEntries() > 0){
	
		TLorentzVector FJ_V, e_V, mu_V;

		// Finding electrons and muons pt and mass distribution
        for (int entry_a = 1; entry_a < branchElectron->GetEntries(); entry_a++){
			electron = (Electron*) branchElectron->At(entry_a);
			e_V = electron->P4();
			eM -> Fill(e_V.M());
			ePt -> Fill(e_V.Pt());
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


  eM -> Draw();
  ePt-> Draw();
}


void Wp_decay_ouput(){

}



