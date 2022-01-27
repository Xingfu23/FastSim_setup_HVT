void rootanalysis(){
	// Load shared library
	gSystem->Load("/wk_cms2/iceeric02/local/root/lib/libPhysics.so");
	gSystem->Load("/wk_cms2/iceeric02/local/MG5_aMC_v2_6_5/ExRootAnalysis/libExRootAnalysis.so");
	
	// Create chain of root tree
	TChain chain("LHEF");
	chain.Add("/wk_cms2/iceeric02/local/MG5_aMC_v2_6_5/BKG_ZH_HToGammagamma_ZTo2L_2/Events/run_01/unweighted_events.root");

	// Create object of class ExRootTreeReader
	ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
	Long64_t numberOfEntries = treeReader->GetEntries();

	// Get pointers to branches used in this analysis
	TClonesArray *branchEvent = treeReader->UseBranch("Event");
	TClonesArray *branchParticle = treeReader->UseBranch("Particle");
	
	TCanvas *c1 = new TCanvas("c1", "Hist1", 800, 600);

	TH1F *h1 = new TH1F("h1", "higgsPT", 100, 0., 200.);

	float a1Px, a1Py, a1Pz, a1E;
	//float a2Px, a2Py, a2Pz, a2E;
	//float DiphotonPT;
	TLorentzVector a1, a2;
	//bool a1True, a2True;
	
	for (int i=0; i<numberOfEntries; i++){
		treeReader->ReadEntry(i);
		TRootLHEFEvent *event = (TRootLHEFEvent*) branchEvent->At(0);
		
		int Particle_Number = event->Nparticles;
		for (int j=0; j<Particle_Number; j++){
			TRootLHEFParticle *particle1=(TRootLHEFParticle*) branchParticle->At(j);
			if (particle1->PID==25){
				a1E  = particle1->E;
				a1Px = particle1->Px;
				a1Py = particle1->Py;
				a1Pz = particle1->Pz;
				a1.SetPxPyPzE(a1Px, a1Py, a1Pz, a1E);
				h1->Fill(a1.Pt());
				/*
				cout << "a1" << a1.Pt() << endl;
				for(int k=j+1; k<Particle_Number; k++){
					TRootLHEFParticle *particle2=(TRootLHEFParticle*) branchParticle->At(k);
					if(particle2->PID==22){
						a2E  = particle2->E;                  
						a2Px = particle2->Px;                 
						a2Py = particle2->Py;                 
						a2Pz = particle2->Pz;                 
						a2.SetPxPyPzE(a2Px, a2Py, a2Pz, a2E);
						cout << "a2: " << a2.Pt() << endl;
						DiphotonPT = (a1+a2).Pt();
						h1->Fill(DiphotonPT);     
					}
				}
				*/
			}
			else continue;
		}
		//DiphotonPT = (a1+a2).Pt();
		//h1->Fill(DiphotonPT);
	}
	c1->cd();
	h1->Draw();
	c1->Update();
	c1->SaveAs("HiggsPt_LHE.pdf");
}
