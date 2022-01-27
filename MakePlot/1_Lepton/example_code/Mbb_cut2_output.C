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

void Prac_Mbb_mass_recon_cut2(const char *inputFile)
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
  //TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");

  // Output root Files
  TFile* outfile = TFile::Open(Form("output_%s", inputFile), "recreate");

  // Book histograms
  TH1 *histMass  = new TH1F("Mbb", " ", 20, 0.0, 200.0);
  TH1 *histMass2 = new TH1F("MZ", " ", 20, 0.0, 200.0);
  TH1 *histMass3 = new TH1F("MZP", " ", 50, 0.0, 4000.0);
  TNtuple *n1 = new TNtuple("n1", "eff", "x");

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
	// Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
                                                                     
    // If event contains at least 1 jet and 2 muon
    if(branchJet->GetEntries() > 0 && branchMuon->GetEntries() > 1){
	
		vector<int> Jbc_index; // c means candidate
		TLorentzVector FJ, Jbb, JTotal;
		TLorentzVector Mu1c, Mu2c;
		TLorentzVector Z, Mu1, Mu2;
		Jet  *jet1, *fatjet;
		Muon *mu1, *mu2;

		// Take the leading and subleading muon
		mu1 = (Muon*) branchMuon -> At(0);
		mu2 = (Muon*) branchMuon -> At(1);
		Mu1c = mu1 -> P4();
		Mu2c = mu2 -> P4();

		// Leptonic pre-selection cuts
		// At least two muons with pT > 55 GeV and 20 GeV for leading and subleading muon, respectively
		// The transverse momentum of the Z boson candidate is required to be at least 200 GeV.
        if (Mu1c.Pt()<55. || Mu2c.Pt()<20.) continue;
		else{
			if (abs(Mu1c.Eta())>=2.4 || abs(Mu2c.Eta())>=2.4) continue;
			else{
				if ((Mu1c+Mu2c).Pt() < 200.) continue;
				else{
					float Zc_mass = (Mu1c + Mu2c).M();
					if (Zc_mass < 70.0 || Zc_mass > 110.0) continue;
					else{
						Mu1 = Mu1c;
						Mu2 = Mu2c;
						Z = Mu1 + Mu2;
						histMass2 -> Fill(Z.M());
					}
				}
			}
		}


		// Hadronic selection
		// The highest-pT AK8 jet in the event is required to have pT > 200 GeV and |η| < 2.5. 
		// If the R value between Jet and any of muons is smaller than 0.8, then ignore this jet.
		// And we ask for the delta phi between fatjet and muon should be greater than 2.5       
		// as well as the difference of eta must smaller than 5.

		for (int entry2=0; entry2<branchJet->GetEntries(); entry2++){
			fatjet = (Jet*) branchJet -> At(entry2);
			FJ = fatjet -> P4();
			float delta_jetmu1 = FJ.DeltaR(Mu1);
			float delta_jetmu2 = FJ.DeltaR(Mu2);
			int jet_Pt_count = 0;

			if (FJ.Pt() > 200. && abs(FJ.Eta()) < 2.5){
				jet_Pt_count += 1;
			}

			if (delta_jetmu1 < 0.8 || delta_jetmu2 < 0.8 || jet_Pt_count == 0) continue;
			else{
				if (abs(Z.DeltaPhi(FJ)) <= 2.5 || abs(Z.Eta() - FJ.Eta()) >= 5.0) continue;
				else{
					if (FJ.M() < 105.0 || FJ.M() > 135.0) continue;
					else{
						Jbc_index.push_back(entry2);
					}
				}
			}
		}

		// Reconstruct bb mass
		if (Jbc_index.size() < 1) continue;
		else{
			jet1 = (Jet*) branchJet->At(Jbc_index[0]);
			Jbb = jet1 -> P4();
			//cout << Jbb.M() << endl;
			histMass -> Fill(Jbb.M());
		}

		histMass3 -> Fill((Z+Jbb).M());

		Jbc_index.clear();
	}  
  }
  
  float N_histMass = histMass->Integral();
  float efficiency = N_histMass/10000.;
  float var[1];
  var[0] = efficiency;
  n1->Fill(var);

  histMass ->Write();
  histMass2->Write();
  histMass3->Write();
  n1       ->Write();
  outfile->Close();
}

void Mbb_cut2_output() {


	Prac_Mbb_mass_recon_cut2("tag_1_delphes_gv1.0_events.root");
	Prac_Mbb_mass_recon_cut2("tag_1_delphes_gv2.0_events.root");
	Prac_Mbb_mass_recon_cut2("tag_1_delphes_gv3.0_events.root");
	Prac_Mbb_mass_recon_cut2("tag_1_delphes_gv4.0_events.root");
	Prac_Mbb_mass_recon_cut2("tag_1_delphes_gv5.0_events.root");
	Prac_Mbb_mass_recon_cut2("tag_1_delphes_gv6.0_events.root");
	Prac_Mbb_mass_recon_cut2("tag_1_delphes_gv7.0_events.root");


}
