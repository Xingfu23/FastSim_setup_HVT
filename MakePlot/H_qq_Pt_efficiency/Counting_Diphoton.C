void Counting_Diphoton(){

	//Choose "One" output root file
	
	TFile *file = TFile::Open("output_Loose_BKG_WGToLNu2G_01Jet_LO_MLM_PTcut_MInf_50k.root");


	TTree* tree = (TTree*) file -> Get("Photontree");

	TH1 *DiPhotonMass_distribution = new TH1F("DiPhotonMass_distribution", "DiPhotonMass_distribution", 100, 0., 200.);

	double DiPhotonMass, DiPhotonPt, LeptonPt;
	int Total_Entries;
	tree->SetBranchAddress("DiPhotonMass", &DiPhotonMass);
	tree->SetBranchAddress("DiPhotonPt", &DiPhotonPt);
	tree->SetBranchAddress("LeptonPt", &LeptonPt);

	int totalcount = tree->GetEntries();
	cout << "total count: " << totalcount << endl;

	//Drawing Diphoton mass distribution
	for(int entry=0; entry<tree->GetEntries(); entry++){
		tree->GetEntry(entry);
		DiPhotonMass_distribution->Fill(DiPhotonMass);
	}
	
	DiPhotonMass_distribution->SetLineColor(9);
	DiPhotonMass_distribution->SetLineWidth(2);
	DiPhotonMass_distribution->SetStats(0);
	DiPhotonMass_distribution->SetAxisRange(0, 180, "X");
	DiPhotonMass_distribution->GetYaxis()->SetTitle("Eentries");
	DiPhotonMass_distribution->GetYaxis()->SetTitleOffset(1.4);
	DiPhotonMass_distribution->GetXaxis()->SetTitle("M_{#gamma#gamma} (GeV)");
	DiPhotonMass_distribution->Draw();

	//Set up Pt cut vector form 0 to 1000
	vector<double> Pt_cut_vector;
	for(int cut=0; cut<21; cut++){
		double Pt_cut=50.*cut;
		Pt_cut_vector.push_back(Pt_cut);
	}

	//Count all events left and the events left in the signal region(121<diphotonmass<128) under different Pt cut in vector
	for(int Pt_index=0; Pt_index<Pt_cut_vector.size(); Pt_index++){
		
		int count=0;
		int total_count_withcut=0;

		for(int entry=0; entry<tree->GetEntries(); entry++){
			tree->GetEntry(entry);

			if(DiPhotonPt>Pt_cut_vector[Pt_index]){
				total_count_withcut += 1;
				if(DiPhotonMass >= 121. && DiPhotonMass <= 128.){
					count += 1;
				}
			}
		}

		cout << "=========================================" << endl;
		cout << "Pt_cut: " << Pt_cut_vector[Pt_index] << endl;
		cout << "Total event under the Pt cut: " << total_count_withcut << endl;
		cout << "Event Counts in Signal Region: " << count << endl;
		cout << "=========================================" << endl;
	}
}
