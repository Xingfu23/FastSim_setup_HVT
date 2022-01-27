void draw_photon(){

	auto c1 = new TCanvas("c1","c1",800,600);     
	auto leg3 = new TLegend(0.58, 0.7, 0.9, 0.9);  
	auto leg4 = new TLegend(0.58, 0.67, 0.9, 0.7); 

	TFile* b1 = new TFile("output_BKG_DiphotonJets_Loosefilter.root", "r");
	TH1F* aPt_b1 = (TH1F*) b1->Get("PhotonPt");

	TFile* b2 = new TFile("output_BKG_DiphotonJets_Test.root", "r");
	TH1F* aPt_b2 = (TH1F*) b2->Get("PhotonPt");

	//TFile* b3 = new TFile("output_BKG_DiphotonJets_Tighterfilter.root", "r");
	//TH1F* aPt_b3 = (TH1F*) b3->Get("PhotonPt");
	
    //Graph option
	aPt_b1->SetStats(0);
	aPt_b1->SetTitle(" ");
	aPt_b1->GetXaxis()->SetTitle("Photon P_{t}(GeV)");
	aPt_b1->GetYaxis()->SetTitleOffset(1.1);
	aPt_b1->GetYaxis()->SetTitle("Events");
	aPt_b1->GetYaxis()->SetTitleOffset(1.2);
	//aPt_b1->GetXaxis()->SetLimits(0, 600);
	aPt_b1->GetXaxis()->SetRangeUser(0., 2000.);

	aPt_b1->SetLineWidth(2);
	aPt_b2->SetLineWidth(2);
	//aPt_b3->SetLineWidth(2);

	aPt_b1->SetLineColor(2);
	aPt_b2->SetLineColor(4);
	//aPt_b3->SetLineColor(8);

	//Show events

	int N_aPt_b1 = aPt_b1->Integral(); 
	int N_aPt_b2 = aPt_b2->Integral();
	//int N_aPt_b3 = aPt_b3->Integral();
	                                                        
	cout << "The event number of b1: " << N_aPt_b1 << endl;
	cout << "The event number of b2: " << N_aPt_b2 << endl;
	//cout << "The event number of b3: " << N_aPt_b3 << endl;
	
	//Normalise
	
	/*
	aPt_s1->Scale(284.44);
	aPt_s2->Scale(14.468);
	aPt_b1->Scale(292.67);
	aPt_b2->Scale(32405.0); 
	aPt_b3->Scale(3174.8); 
	aPt_b4->Scale(7561.0); 
	aPt_b5->Scale(131630000.);  
	aPt_b6->Scale(7044900.); 
	aPt_b7->Scale(173110.); 
	aPt_b8->Scale(2070.9);  
	*/

	// Draw option, make plot
	
	c1->SetLogy();                 
	aPt_b1->SetMinimum(1);   
	aPt_b1->SetMaximum(1000);

	aPt_b1->Draw();
	aPt_b2->Draw("same");
	//aPt_b3->Draw("same");

	// legend option
	
	leg3->SetHeader("W' decay SM background ");
	//leg3->SetNColumns(2);
	leg3->AddEntry(aPt_b1, "DiphotonJets_Loose");
	leg3->AddEntry(aPt_b2, "DiphotonJets_Test");
	//leg3->AddEntry(aPt_b3, "DiphotonJets_Tighter");

	leg3->SetTextSize(0.025);
	leg4->SetHeader("g_{v}=4, c_{H}=-1, c_{F}=1");
	leg4->SetTextSize(0.02);                      
	                                              
	leg3->Draw();                                 
	leg4->Draw();                                 
}
