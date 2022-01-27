void draw_lep_pt(){

	auto c1 = new TCanvas("c1","c1",800,600);     
	auto leg3 = new TLegend(0.58, 0.7, 0.9, 0.9);  
	auto leg4 = new TLegend(0.58, 0.67, 0.9, 0.7); 

	TFile* s1 = new TFile("output_HVT_QQToWpToNuL2b_3TeV.root", "r");
	TH1F *ePt_s1 = (TH1F*) s1->Get("ElectronPt");
	TH1F *muPt_s1 = (TH1F*) s1->Get("MuonPt");

	TFile* s2 = new TFile("output_HVT_QQToWpToNuL2Q_3TeV.root", "r");
	TH1F *ePt_s2 = (TH1F*) s2->Get("ElectronPt");
	TH1F *muPt_s2 = (TH1F*) s2->Get("MuonPt");

    TFile* b1 = new TFile("output_BKG_ttWJetToLNu_LO_MLM_cut3.root", "r");
	TH1F *ePt_b1 = (TH1F*) b1->Get("ElectronPt");
	TH1F *muPt_b1 = (TH1F*) b1->Get("MuonPt");

	TFile* b2 = new TFile("output_BKG_WZToLNu2Q_LO_MLM_cut3.root", "r");
	TH1F *ePt_b2 = (TH1F*) b2->Get("ElectronPt");
	TH1F *muPt_b2 = (TH1F*) b2->Get("MuonPt");
    
	TFile* b3 = new TFile("output_BKG_WZToL3Nu_LO_MLM_cut3.root", "r");
	TH1F *ePt_b3 = (TH1F*) b3->Get("ElectronPt");
	TH1F *muPt_b3 = (TH1F*) b3->Get("MuonPt");

	TFile* b4 = new TFile("output_BKG_WWToLNu2Q_4f_LO_MLM_cut3.root", "r");
	TH1F *ePt_b4 = (TH1F*) b4->Get("ElectronPt");
	TH1F *muPt_b4 = (TH1F*) b4->Get("MuonPt");

	TFile* b5 = new TFile("output_BKG_WJetsToLNu_LO_MLM_cut3.root", "r");
	TH1F *ePt_b5 = (TH1F*) b5->Get("ElectronPt");
	TH1F *muPt_b5 = (TH1F*) b5->Get("MuonPt");

	TFile* b6 = new TFile("output_BKG_ST_s-channel_4f_leptonDecays_LO_cut3.root", "r");
	TH1F *ePt_b6 = (TH1F*) b6->Get("ElectronPt");
	TH1F *muPt_b6 = (TH1F*) b6->Get("MuonPt");

	TFile* b7 = new TFile("output_BKG_ST_t-channel_4f_inclusiveDecays_LO_cut3.root", "r");
	TH1F *ePt_b7 = (TH1F*) b7->Get("ElectronPt");
	TH1F *muPt_b7 = (TH1F*) b7->Get("MuonPt");

	TFile* b8 = new TFile("output_BKG_WH_HToBB_WToLNu.root", "r");
	TH1F *ePt_b8 = (TH1F*) b8->Get("ElectronPt");
	TH1F *muPt_b8 = (TH1F*) b8->Get("MuonPt");   
	
    //Graph option
	ePt_s2->SetStats(0);
	ePt_s2->SetTitle(" ");
    ePt_s2->GetXaxis()->SetTitle("Electron P_{t}(GeV)");
	ePt_s2->GetYaxis()->SetTitleOffset(1.1);
	ePt_s2->GetYaxis()->SetTitle("Events");
	ePt_s2->GetYaxis()->SetTitleOffset(1.2);
	ePt_s2->GetXaxis()->SetLimits(0, 1600);

	ePt_s1->SetLineWidth(2);
	ePt_s2->SetLineWidth(2);
	ePt_b1->SetLineWidth(2);
	ePt_b2->SetLineWidth(2);
	ePt_b3->SetLineWidth(2);
	ePt_b4->SetLineWidth(2);
	ePt_b5->SetLineWidth(2);
	ePt_b6->SetLineWidth(2);
	ePt_b7->SetLineWidth(2);
	ePt_b8->SetLineWidth(2);

	ePt_s1->SetLineColor(9);
	ePt_s1->SetFillColor(9);
	ePt_s2->SetLineColor(38);
    ePt_b1->SetLineColor(2);
    ePt_b2->SetLineColor(8);
    ePt_b3->SetLineColor(28);
    ePt_b4->SetLineColor(12);
    ePt_b5->SetLineColor(92);
	ePt_b6->SetLineColor(87);
	ePt_b7->SetLineColor(29);
	ePt_b8->SetLineColor(46);
	ePt_b8->SetFillColor(46);

	//Show events

	int N_ePt_s1 = ePt_s1->Integral();  
	int N_ePt_s2 = ePt_s2->Integral();
	int N_ePt_b1 = ePt_b1->Integral();                    
	int N_ePt_b2 = ePt_b2->Integral();                    
	int N_ePt_b3 = ePt_b3->Integral();                    
	int N_ePt_b4 = ePt_b4->Integral();                    
	int N_ePt_b5 = ePt_b5->Integral();                    
	int N_ePt_b6 = ePt_b6->Integral();                    
	int N_ePt_b7 = ePt_b7->Integral();                    
	int N_ePt_b8 = ePt_b8->Integral();                    
	                                                        
	cout << "The event number of s1: " << N_ePt_s1 << endl;
	cout << "The event number of s2: " << N_ePt_s2 << endl;
	cout << "The event number of b1: " << N_ePt_b1 << endl;
	cout << "The event number of b2: " << N_ePt_b2 << endl;
	cout << "The event number of b3: " << N_ePt_b3 << endl;
	cout << "The event number of b4: " << N_ePt_b4 << endl;
	cout << "The event number of b5: " << N_ePt_b5 << endl;
	cout << "The event number of b6: " << N_ePt_b6 << endl;
	cout << "The event number of b7: " << N_ePt_b7 << endl;
	cout << "The event number of b8: " << N_ePt_b8 << endl;

	//Normailize
	
		
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
	

	// Draw option, make plot
	
	c1->SetLogy();                 
	ePt_s2->SetMinimum(1);   
	ePt_s2->SetMaximum(1000000000000);

	      
	ePt_s2->Draw();
	ePt_b1->Draw("same");
	ePt_b2->Draw("same");
	ePt_b3->Draw("same");
	ePt_b4->Draw("same");
	ePt_b5->Draw("same");
	ePt_b6->Draw("same");
	ePt_b7->Draw("same");
	ePt_b8->Draw("same");
	ePt_s1->Draw("same");

	// legend option
	
	leg3->SetHeader("M_{Z'}/M_{W'}= 3TeV ");
	leg3->SetNColumns(2);
	leg3->AddEntry(ePt_s1, "W'> WH(bb)");
	leg3->AddEntry(ePt_s2, "W'> WZ(jj)");
	leg3->AddEntry(ePt_b1, "tt~ > WZj");
	leg3->AddEntry(ePt_b2, "WZ > LNu2Q");
	leg3->AddEntry(ePt_b3, "WZ > L3Nu");
	leg3->AddEntry(ePt_b4, "WW > LNu2Q");
	leg3->AddEntry(ePt_b5, "Wj > LNu");
	leg3->AddEntry(ePt_b6, "ST s-channel");
	leg3->AddEntry(ePt_b7, "ST t-channel");
	leg3->AddEntry(ePt_b8, "WH > LNubb");

	leg3->SetTextSize(0.03);
	leg4->SetHeader("g_{v}=4, c_{H}=-1, c_{F}=1");
	leg4->SetTextSize(0.02);                      
	                                              
	leg3->Draw();                                 
	leg4->Draw();                                 
}
