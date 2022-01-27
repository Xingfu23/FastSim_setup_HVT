void draw_jetpt1(){

	auto c1 = new TCanvas("c1","c1",800,600);
    auto leg3 = new TLegend(0.6, 0.7, 0.90, 0.90);
	auto leg4 = new TLegend(0.6, 0.67, 0.9, 0.7);

	TFile* s1 = new TFile("output_HVT_QQToWpToNuL2b.root", "r");
	TH1F *misEt_s1 = (TH1F*) s1->Get("MissingEt");
	TH1F *jetpt_s1 = (TH1F*) s1->Get("fatjetPt");

	TFile* b1 = new TFile("output_BKG_ttWJetToLNu_LO_MLM.root", "r");
	TH1F *misEt_b1 = (TH1F*) b1->Get("MissingEt");
	TH1F *jetpt_b1 = (TH1F*) b1->Get("fatjetPt");

	TFile* b2 = new TFile("output_BKG_WZToLNu2Q_LO_MLM.root", "r");
	TH1F *misEt_b2 = (TH1F*) b2->Get("MissingEt");
	TH1F *jetpt_b2 = (TH1F*) b2->Get("fatjetPt");

	TFile* b3 = new TFile("output_BKG_WZToL3Nu_LO_MLM.root", "r");
	TH1F *misEt_b3 = (TH1F*) b3->Get("MissingEt");
	TH1F *jetpt_b3 = (TH1F*) b3->Get("fatjetPt");

	TFile* b4 = new TFile("output_BKG_WWToLNu2Q_4f_LO_MLM.root", "r");
	TH1F *misEt_b4 = (TH1F*) b4->Get("MissingEt");
	TH1F *jetpt_b4 = (TH1F*) b4->Get("fatjetPt");

	TFile* b5 = new TFile("output_BKG_WJetsToLNu_LO_MLM.root", "r");
	TH1F *misEt_b5 = (TH1F*) b5->Get("MissingEt");
	TH1F *jetpt_b5 = (TH1F*) b5->Get("fatjetPt");

	TFile* b6 = new TFile("output_BKG_ST_s-channel_4f_leptonDecays_LO.root", "r");
	TH1F *misEt_b6 = (TH1F*) b6->Get("MissingEt");
	TH1F *jetpt_b6 = (TH1F*) b6->Get("fatjetPt");

	TFile* b7 = new TFile("output_BKG_ST_t-channel_4f_inclusiveDecays_LO.root", "r");
	TH1F *misEt_b7 = (TH1F*) b7->Get("MissingEt");
	TH1F *jetpt_b7 = (TH1F*) b7->Get("fatjetPt");
	
    TFile* b8 = new TFile("output_BKG_WH_HToBB_WToLNu.root", "r");
	TH1F *misEt_b8 = (TH1F*) b8->Get("MissingEt");
	TH1F *jetpt_b8 = (TH1F*) b8->Get("fatjetPt");



	// Graph option
	jetpt_s1->SetStats(0);
	jetpt_s1->SetTitle(" ");
	jetpt_s1->GetXaxis()->SetTitle("Jet P_{t} (GeV)");
	jetpt_s1->GetYaxis()->SetTitle("Normalized Luminosity");
	jetpt_s1->GetYaxis()->SetTitleOffset(1.4);
    
	jetpt_s1->Scale(1./0.509);                    
	jetpt_b1->Scale(1./34.28);                   
	jetpt_b2->Scale(1./0.077);                   
	jetpt_b3->Scale(1./0.177);                   
	jetpt_b4->Scale(1./0.0108);                   
	jetpt_b5->Scale(1./0.000001);                   
	jetpt_b6->Scale(1./0.012);                   
	jetpt_b7->Scale(1./0.0456);
	jetpt_b8->Scale(1./11.90);
	
	jetpt_s1->SetLineWidth(3);
	jetpt_b1->SetLineWidth(3);
	jetpt_b2->SetLineWidth(3);
	jetpt_b3->SetLineWidth(3);
	jetpt_b4->SetLineWidth(3);
	jetpt_b5->SetLineWidth(3);
	jetpt_b6->SetLineWidth(3);
	jetpt_b7->SetLineWidth(3);
	jetpt_b8->SetLineWidth(3);

	jetpt_s1->SetLineColor(46);
	jetpt_s1->SetFillColor(46);
	jetpt_b1->SetLineColor(2);
	jetpt_b2->SetLineColor(8);
	jetpt_b3->SetLineColor(28);
	jetpt_b4->SetLineColor(12);
	jetpt_b5->SetLineColor(92);
	jetpt_b6->SetLineColor(87);
	jetpt_b7->SetLineColor(29);
	jetpt_b8->SetLineColor(4);
    

	c1->SetLogy();
	jetpt_s1->SetMinimum(0.0001);
	jetpt_s1->SetMaximum(1000000000.);
	jetpt_s1->Draw();
	jetpt_b1->Draw("same");
	jetpt_b2->Draw("same");
	jetpt_b3->Draw("same");
	jetpt_b4->Draw("same");
	jetpt_b5->Draw("same");
	jetpt_b6->Draw("same");
	jetpt_b7->Draw("same");
	jetpt_b8->Draw("same");
	
	/*
	//Show event left
	
	
	int N_jetpt_s1 = jetpt_s1->Integral();
	int N_jetpt_b1 = jetpt_b1->Integral();
	int N_jetpt_b2 = jetpt_b2->Integral();
	int N_jetpt_b3 = jetpt_b3->Integral();
	int N_jetpt_b4 = jetpt_b4->Integral();
	int N_jetpt_b5 = jetpt_b5->Integral();
	int N_jetpt_b6 = jetpt_b6->Integral();
	int N_jetpt_b7 = jetpt_b7->Integral();
	int N_jetpt_b8 = jetpt_b8->Integral();

	cout << "The event number of s1: " << N_jetpt_s1 << endl;
	cout << "The event number of b1: " << N_jetpt_b1 << endl;
	cout << "The event number of b2: " << N_jetpt_b2 << endl;
	cout << "The event number of b3: " << N_jetpt_b3 << endl;
	cout << "The event number of b4: " << N_jetpt_b4 << endl;
	cout << "The event number of b5: " << N_jetpt_b5 << endl;
    cout << "The event number of b6: " << N_jetpt_b6 << endl;
	cout << "The event number of b7: " << N_jetpt_b7 << endl;
	cout << "The event number of b8: " << N_jetpt_b8 << endl;
    */ 


	// legend option
	
	leg3->SetHeader("M_{Z'}/M_{W'}=2TeV, 100000 events");
    leg3->SetNColumns(2);
	leg3->AddEntry(jetpt_s1, "W'> WH(bb)x1000");
	leg3->AddEntry(jetpt_b1, "tt~ > WZj");
	leg3->AddEntry(jetpt_b2, "WZ > LNu2Q");
	leg3->AddEntry(jetpt_b3, "WZ > L3Nu");
	leg3->AddEntry(jetpt_b4, "WW > LNu2Q");
	leg3->AddEntry(jetpt_b5, "Wj > LNu");
	leg3->AddEntry(jetpt_b6, "ST s-channel");
	leg3->AddEntry(jetpt_b7, "ST t-channel");
	leg3->AddEntry(jetpt_b8, "WH > LNubb");
	leg3->SetTextSize(0.02);
	
	leg4->SetHeader("g_{v}=3, c_{H}=-1, c_{F}=1");
	leg4->SetTextSize(0.02);                      

	leg3->Draw();
	leg4->Draw();

}
