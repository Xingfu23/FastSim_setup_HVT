void draw_lep_pt(){

	auto c1 = new TCanvas("c1","c1",800,600);     
	auto leg3 = new TLegend(0.58, 0.7, 0.9, 0.9);  
	auto leg4 = new TLegend(0.58, 0.67, 0.9, 0.7); 

	TFile* b1 = new TFile("output_BKG_DiphotonJets_Loosefilter.root", "r");
	TH1F *ePt_b1 = (TH1F*) b1->Get("ElectronPt");
	TH1F *muPt_b1 = (TH1F*) b1->Get("MuonPt");

	TFile* b2 = new TFile("output_BKG_DiphotonJets_Test.root", "r");
	TH1F *ePt_b2 = (TH1F*) b2->Get("ElectronPt");                          
	TH1F *muPt_b2 = (TH1F*) b2->Get("MuonPt");                             
	
    //Graph option
	ePt_b1->SetStats(0);
	ePt_b1->SetTitle(" ");
	ePt_b1->GetXaxis()->SetTitle("Electron P_{t}(GeV)");
	ePt_b1->GetYaxis()->SetTitleOffset(1.1);
	ePt_b1->GetYaxis()->SetTitle("Events");
	ePt_b1->GetYaxis()->SetTitleOffset(1.2);
	//ePt_b1->GetXaxis()->SetLimits(0, 600);
	ePt_b1->GetXaxis()->SetRangeUser(0., 1000.);

	ePt_b1->SetLineWidth(2);
	ePt_b2->SetLineWidth(2);

	ePt_b1->SetLineColor(2);
	ePt_b2->SetLineColor(4);

	//Show events

	int N_ePt_b1 = ePt_b1->Integral(); 
	int N_ePt_b2 = ePt_b2->Integral();
	                                                        
	cout << "The event number of b1: " << N_ePt_b1 << endl;
	cout << "The event number of b2: " << N_ePt_b2 << endl;
	
	//Normalise
	
	/*
	ePt_s1->Scale(284.44);
	ePt_s2->Scale(14.468);
	ePt_b1->Scale(292.67);
	ePt_b2->Scale(32405.0); 
	ePt_b3->Scale(3174.8); 
	ePt_b4->Scale(7561.0); 
	ePt_b5->Scale(131630000.);  
	ePt_b6->Scale(7044900.); 
	ePt_b7->Scale(173110.); 
	ePt_b8->Scale(2070.9);  
	*/

	// Draw option, make plot
	
	c1->SetLogy();                 
	ePt_b1->SetMinimum(1);   
	ePt_b1->SetMaximum(1000);

	ePt_b1->Draw();
	ePt_b2->Draw("same");

	// legend option
	
	leg3->SetHeader("W' decay:SM background ");
	//leg3->SetNColumns(2);
	leg3->AddEntry(ePt_b1, "DophotonJets_Loose");
	leg3->AddEntry(ePt_b2, "DiphotonJets_Test");

	leg3->SetTextSize(0.025);
	leg4->SetHeader("g_{v}=4, c_{H}=-1, c_{F}=1");
	leg4->SetTextSize(0.02);                      
	                                              
	leg3->Draw();                                 
	leg4->Draw();                                 
}
