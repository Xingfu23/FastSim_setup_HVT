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

  //double PhotonPt, PhotonMass, PhotonEta;
  double DiPhotonMass, DiPhotonPt;

  // Book Tree
  TTree *Photontree = new TTree("Photontree", "Photontree");

  //Setting branch
  Photontree->Branch("DiPhotonMass", &DiPhotonMass, "DiPhotonMass/D");
  Photontree->Branch("DiPhotonPt", &DiPhotonPt, "DiPhotonPt/D");

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry) {
	// Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

	// If events have at least 2 photon and 1 muon.
	if(branchPhoton->GetEntries()>1){
		if(branchMuon->GetEntries() > 0 && branchElectron->GetEntries() == 0){
			
			// Take the first and second photon reconstructing diphoton mass and momentum
			// The leading photon must greater than (3/8)*diphoton mass
			// And the subleading photon must greater than (1/4)*diphoton mass
			// At least one lepton with PT > 20GeV
			// Missing transverse momentum pT > 45 GeV
			// For direction restricton, we ask R(photon,e) > 1.0, R(photon, mu) > 0.5, for each of the leptons.
			// There are 2 jets at most and each satisfying pT > 20GeV, |eta|< 2.4, R(jet, lepton) > 0.4 and R(jet, photon) > 0.4.   

			TLorentzVector a1, a2, mu1, mET;
			Photon *photon1, *photon2;
 
			photon1 = (Photon*) branchPhoton->At(0);
			photon2 = (Photon*) branchPhoton->At(1);
			a1 = photon1->P4();
			a2 = photon2->P4();

			muon1     = (Muon*) branchMuon->At(0);
			missingET = (MissingET*) branchMissingET->At(0);
			mu1 = muon1->P4();
			mET = missingET->P4();

			DiPhotonMass = (a1+a2).M();
			DiPhotonPt   = (a1+a2).Pt();

			if(a1.Pt()<(0.375)*DiPhotonMass || a2.Pt()<(0.25)*DiPhotonMass) continue;
				if(mu1.Pt()<20. || mET.Pt()<45.) continue;

				// Direction restrictions
				for(int entry1=0; entry1<branchPhoton->GetEntries(); entry1++){
					for(int entry2=0; entry2<branchMuon->GetEntries(); entry2++){

						TLorentzVector a3, mu3;
						photon3 = (Photon*) branchPhoton->At(entry1);
						muon3   = (Muon*) branchMuon->At(entry2);
						a3  = photon3->P4();
						mu3 = muon3->P4();
						double deltaR1 = a3.DeltaR(mu3);

						if(deltaR1<0.5) continue;
							// Jet selections 
							if(branchJet->GetEntries() > 3) continue;
							else if(branchJet->GetEntries() == 0){
								Photontree->Fill();
							}
							else{
								for(int entry3=0; entry3<branchJet->GetEntries(); entry3++){
									
									TLorentzVector jet1;
									jet = (Jet*) branchJet -> At(entry3);
									jet1 = jet->P4();
									if(abs(jet1.Eta()>2.4) || jet1.Pt()<20.) continue;
										double deltaR2 = jet1.DeltaR(mu3);
										double deltaR3 = jet1.DeltaR(a3);
										if(deltaR2<0.4 || deltaR3<0.4) continue;
											Photontree->Fill();
								}
							}
					}
				}
		}
		
		// If events have at least 2 photon and 1 electron
		// The event selection is the same as 1 muon scenarios besides some lepton constrain
		else if(branchMuon->GetEntries() == 0 && branchElectron->GetEntries() > 0){
			TLorentzVector a1, a2, e1, mET;                
			Photon *photon1, *photon2;                      
			                                                
			photon1 = (Photon*) branchPhoton->At(0);        
			photon2 = (Photon*) branchPhoton->At(1);        
			a1 = photon1->P4();                             
			a2 = photon2->P4();                             
			                                                
			electron1 = (Electron*) branchElectron->At(0);          
			missingET = (MissingET*) branchMissingET->At(0);
			e1  = electron1->P4();                              
			mET = missingET->P4();                          
			
			DiPhotonMass = (a1+a2).M(); 
			DiPhotonPt   = (a1+a2).Pt();
			
			if(a1.Pt()<(0.375)*DiPhotonMass || a2.Pt()<(0.25)*DiPhotonMass) continue;
			    if(e1.Pt()<20. || mET.Pt()<45.) continue;

				// Direction restrictions
				for(int entry1=0; entry1<branchPhoton->GetEntries(); entry1++){  
					for(int entry2=0; entry2<branchElectron->GetEntries(); entry2++){
						
						TLorentzVector a3, e3;                      
						photon3   = (Photon*) branchPhoton->At(entry1);
						electron3 = (Electron*) branchElectron->At(entry2);    
						a3 = photon3->P4();                         
						e3 = electron3->P4();                           
						double deltaR1 = a3.DeltaR(e3);             
						
						if(deltaR1<1.0) continue;
							// Jet selections
							if(branchJet->GetEntries()>3) continue;
							else if(branchJet->GetEntries()==0){
								Photontree->Fill();
							}
							else{
								for(int entry3=0; entry3<branchJet->GetEntries(); entry3++){
									TLorentzVector jet1;                                    
									jet = (Jet*) branchJet -> At(entry3);                   
									jet1 = jet->P4();                                       
									if(abs(jet1.Eta()>2.4) || jet1.Pt()<20.) continue;      
										double deltaR2 = jet1.DeltaR(e3);                   
										double deltaR3 = jet1.DeltaR(a3);                    
										if(deltaR2<0.4 || deltaR3<0.4) continue;              
											Photontree->Fill();                             
								}                                                           
							}
						}
				}
		}

	}                                                            
	
  }	

 Photontree->Write();


 outfile->Close();
}

// Main output process
void Wp_decay_output_DiPhotonMass(){

	Wp_decay_graph_output("BKG_DiphotonJets_LO_MLM.root");
	cout << "output done" << endl;
	Wp_decay_graph_output("BKG_GJets_LO_MLM.root");
	cout << "output done" << endl;
	Wp_decay_graph_output("BKG_WGToLNuG_01Jet_LO_MLM.root");
	cout << "output done" << endl;

	cout << "process end" << endl;
}

