void draw_electron_pt(){

	auto c1 = new TCanvas("c1","c1",800,600);
	auto leg3 = new TLegend(0.6, 0.7, 0.9, 0.9);
	auto leg4 = new TLegend(0.6, 0.67, 0.9, 0.7);

	TFile* s1 = new TFile("output_HVT_QQToWpToNuL2b_2.root", "r");
	TH1F *ePt_s1 = (TH1F*) s1->Get("ElectronPt");
	TH1F *muPt_s1 = (TH1F*) s1->Get("MuonPt");

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
	
	// Show events left
	
	int N_ePt_s1 = ePt_s1->Integral();
	int N_ePt_b1 = ePt_b1->Integral();
	int N_ePt_b2 = ePt_b2->Integral();
	int N_ePt_b3 = ePt_b3->Integral();
	int N_ePt_b4 = ePt_b4->Integral();
	int N_ePt_b5 = ePt_b5->Integral();
	int N_ePt_b6 = ePt_b6->Integral();
	int N_ePt_b7 = ePt_b7->Integral();
	int N_ePt_b8 = ePt_b8->Integral();

	cout << "The event number of s1: " << N_ePt_s1 << endl;
	cout << "The event number of b1: " << N_ePt_b1 << endl;
	cout << "The event number of b2: " << N_ePt_b2 << endl;
	cout << "The event number of b3: " << N_ePt_b3 << endl;
	cout << "The event number of b4: " << N_ePt_b4 << endl;
	cout << "The event number of b5: " << N_ePt_b5 << endl;
	cout << "The event number of b6: " << N_ePt_b6 << endl;
	cout << "The event number of b7: " << N_ePt_b7 << endl;
	cout << "The event number of b8: " << N_ePt_b8 << endl;
	
	//Graph option
	
	ePt_s1->SetStats(0);
    ePt_s1->SetTitle(" ");
    ePt_s1->GetXaxis()->SetTitle("Electron P_{t}(GeV)");
	ePt_s1->GetYaxis()->SetTitle("Normalized Luminosity");
	ePt_s1->GetYaxis()->SetTitleOffset(1.4);

	ePt_s1->Scale(1./6.13);
	ePt_b1->Scale(1./2280.7);
	ePt_b2->Scale(1./194.4);
	ePt_b3->Scale(1./553.0);
	ePt_b4->Scale(1./101.6);
	ePt_b5->Scale(1./0.011);
    ePt_b6->Scale(1./11.20);
	ePt_b7->Scale(1./0.458);
	ePt_b8->Scale(1./62.17);

	ePt_s1->SetLineWidth(3);
	ePt_b1->SetLineWidth(3);
	ePt_b2->SetLineWidth(3);
	ePt_b3->SetLineWidth(3);
	ePt_b4->SetLineWidth(3);
	ePt_b5->SetLineWidth(3);
	ePt_b6->SetLineWidth(3);
	ePt_b7->SetLineWidth(3);
	ePt_b8->SetLineWidth(3);

	ePt_s1->SetLineColor(46);
	ePt_s1->SetFillColor(46);
    ePt_b1->SetLineColor(2);
    ePt_b2->SetLineColor(8);
    ePt_b3->SetLineColor(28);
    ePt_b4->SetLineColor(12);
    ePt_b5->SetLineColor(92);
	ePt_b6->SetLineColor(87);
	ePt_b7->SetLineColor(29);
	ePt_b8->SetLineColor(4);
    
	c1->SetLogy();
	ePt_s1->SetMinimum(0.0001);
	ePt_s1->SetMaximum(10000000.);
	ePt_s1->Draw();
	ePt_b1->Draw("same");
	ePt_b2->Draw("same");
	ePt_b3->Draw("same");
	ePt_b4->Draw("same");
	ePt_b5->Draw("same");
	ePt_b6->Draw("same");
	ePt_b7->Draw("same");
	ePt_b8->Draw("same");
	
	// legend option
	leg3->SetHeader("M_{Z'}/M_{W'}=2TeV, 100000 events");
	leg3->SetNColumns(2);
	leg3->AddEntry(ePt_s1, "W'> WH(bb)x100");
	leg3->AddEntry(ePt_b1, "tt~ > WZj");
	leg3->AddEntry(ePt_b2, "WZ > LNu2Q");
	leg3->AddEntry(ePt_b3, "WZ > L3Nu");
	leg3->AddEntry(ePt_b4, "WW > LNu2Q");
	leg3->AddEntry(ePt_b5, "Wj > LNu");
	leg3->AddEntry(ePt_b6, "ST s-channel");
	leg3->AddEntry(ePt_b7, "ST t-channel");
	leg3->AddEntry(ePt_b8, "WH > LNubb");

	leg3->SetTextSize(0.02);

	leg4->SetHeader("g_{v}=3, c_{H}=-1, c_{F}=1");
	leg4->SetTextSize(0.02);

	leg3->Draw();
	leg4->Draw();
}

