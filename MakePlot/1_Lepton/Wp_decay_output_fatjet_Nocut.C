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

void Wp_decay_output_fatjet_Nocut(const char *inputFile)
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
  //TFile* outfile = TFile::Open(Form("output_counting_%s", inputFile), "recreate");

  // Book Canvas
  //TCanvas *c= new TCanvas ("c","Test Canvas", 800, 600);

  // Book histograms
  TH1 *fatjetPt = new TH1F("fatjetPt", "fatjetPt", 100, 0., 1600.);
  TH1 *fatjetM1 = new TH1F("fatjetMass1", "fatjetMass1", 100, 0., 500.);
  TH1 *fatjetM2 = new TH1F("fatjetMass2", "fatjetMass2", 100, 0., 500.);
  TH1 *fatjetM  = new TH1F("fatjetMass", "fatjetMass", 100, 0., 500.);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
	// Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
                                                                     
    // If event contains at least 1 jet and 1 muon
    if (branchJet->GetEntries() > 0 && branchElectron->GetEntries() > 0){
		
		TLorentzVector FJ, FJ1, lep_c, lep;             
		TLorentzVector MisET_c, MisET, Jbb;        
		vector<int> Jbc_index; // c means candidate

		// leptonic pre-selection cut:                                                           
		// For electron its pt need to be greater than 55 GeV,                                   
		// and for muon, whose pt is greater than 135 GeV.                                       
		// Multijet background is reduced by requiring Et_missing > 80 GeV,                      
		// and we ask delta_phi(lepton, pt_missing) < 2 as well as delta_phi(jet, pt_missing) > 2

		lep_c = ((Electron*)branchElectron->At(0))->P4();       
		MisET_c = ((MissingET*) branchMissingET -> At(0))->P4();
		                                                        
		float delta_phi_lepmisET = lep_c.DeltaPhi(MisET_c);     
		                                                        
		if (lep_c.Pt()<55. || MisET_c.Et()<80.) continue;       
		else{                                                   
			if (delta_phi_lepmisET > 2.) continue;              
			else{                                               
				lep = lep_c;                                    
				MisET = MisET_c;                                
			}                                                   
		}  
		// Hadronic selection                                                                  
		// The highest-pT AK8 jet in the event is required to have pT > 200 GeV and |η| < 2.5  
		// The pruned jet mass mj must satisfy 105 < mj < 135 GeV.                             
		// delta_phi(jet, pt_missing) > 2                                                      
		
		for (int entry2=0; entry2<branchJet->GetEntries(); entry2++){ 
			fatjet = (Jet*) branchJet -> At(entry2);                  
			FJ = fatjet->P4();                                                                        
			float delta_R_lepjet = FJ.DeltaR(lep);                    
			float delta_Phi_jetmisET = FJ.DeltaPhi(MisET);            
			int jet_Pt_count = 0;                                     
					
			    if (delta_R_lepjet < 0.8) continue;                                                
				else{
					if (FJ.Pt() < 200. || abs(FJ.Eta()) > 2.5 || delta_Phi_jetmisET < 2.) continue;
					else{                                                                          
						jet_Pt_count += 1;                                                         
						if (jet_Pt_count == 0) continue;                                           
						else{                                                                      
							Jbc_index.push_back(entry2);                                           
						}                                                                          
					}                                                                              
				}                                                                                  
		}

		if (Jbc_index.size()<1) continue;             
		else{                                         
			jet1 = (Jet*) branchJet->At(Jbc_index[0]);
			FJ1 = jet1->P4();
			fatjetM1->Fill(FJ1.M());
	}
  }
	else if (branchJet->GetEntries() > 0 && branchMuon->GetEntries() > 0 && branchElectron->GetEntries()==0){
	                                                
		TLorentzVector FJ, FJ1, lep_c, lep;           
		TLorentzVector MisET_c, MisET, Jbb;           
		vector<int> Jbc_index; // c means candidate

		// leptonic pre-selection cut:                                                           
		// For electron its pt need to be greater than 55 GeV,                                   
		// and for muon, whose pt is greater than 135 GeV.                                       
		// Multijet background is reduced by requiring Et_missing > 80 GeV,                      
		// and we ask delta_phi(lepton, pt_missing) < 2 as well as delta_phi(jet, pt_missing) > 2
		
		lep_c = ((Muon*)branchMuon->At(0))->P4();        
		MisET_c = ((MissingET*) branchMissingET -> At(0))->P4(); 
		                                                         
		float delta_phi_lepmisET = lep_c.DeltaPhi(MisET_c);      
		                                                         
		if (lep_c.Pt()<135. || MisET_c.Et()<80.) continue;        
		else{                                                    
			if (delta_phi_lepmisET > 2.) continue;               
			else{                                                
				lep = lep_c;                                     
				MisET = MisET_c;                                 
			}                                                    
		} 
		// Hadronic selection                                                                
		// The highest-pT AK8 jet in the event is required to have pT > 200 GeV and |η| < 2.5
		// The pruned jet mass mj must satisfy 105 < mj < 135 GeV.                           
		// delta_phi(jet, pt_missing) > 2
		
		for (int entry2=0; entry2<branchJet->GetEntries(); entry2++){                               
			fatjet = (Jet*) branchJet -> At(entry2);                                                
			FJ = fatjet->P4();                                                                      
			float delta_R_lepjet = FJ.DeltaR(lep);                                                  
			float delta_Phi_jetmisET = FJ.DeltaPhi(MisET);                                          
			int jet_Pt_count = 0;                                                                   
								                                                                                            
			if (delta_R_lepjet < 0.8) continue;                                                 
			else{                                                                               
				if (FJ.Pt() < 200. || abs(FJ.Eta()) > 2.5 || delta_Phi_jetmisET < 2.) continue; 
				else{                                                                           
					jet_Pt_count += 1;                                                          
					if (jet_Pt_count == 0) continue;                                            
					else{
						Jbc_index.push_back(entry2);
					}
				}
			}

			if (Jbc_index.size()<1) continue;              
			else{                                          
				jet1 = (Jet*) branchJet->At(Jbc_index[0]); 
				FJ1 = jet1->P4();                          
			    fatjetM2->Fill(FJ1.M());
			}
		}
	}

	

  fatjetM->Clone("fatjetM1");
  fatjetM->Add(fatjetM2);
  fatjetM->Draw();
  //fatjetM2->Draw("same");
  //outfile->Close(); 
  }
}



