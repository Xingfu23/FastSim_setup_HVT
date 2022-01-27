void draw_fatjet_K(){

	auto c1 = new TCanvas("c1","c1",800,600);     
	auto leg3 = new TLegend(0.58, 0.7, 0.9, 0.9);  
	auto leg4 = new TLegend(0.58, 0.67, 0.9, 0.7); 

	TFile* s1 = new TFile("output_HVT_QQToWpToNuL2b_3TeV.root", "r");
	TH1F *fatjetPt_s1  = (TH1F*) s1->Get("fatjetPt");
	TH1F *fatjetM_s1   = (TH1F*) s1->Get("fatjetMass");
	TH1F *fatjetEta_s1 = (TH1F*) s1->Get("fatjetEta");

	TFile* s2 = new TFile("output_HVT_QQToWpToNuL2Q_3TeV.root", "r");
	TH1F *fatjetPt_s2  = (TH1F*) s2->Get("fatjetPt");
	TH1F *fatjetM_s2   = (TH1F*) s2->Get("fatjetMass");
	TH1F *fatjetEta_s2 = (TH1F*) s2->Get("fatjetEta");
	TH1F *ePt_s2 = (TH1F*) s2->Get("ElectronPt");

    TFile* b1 = new TFile("output_BKG_ttWJetToLNu_LO_MLM_cut3.root", "r");
	TH1F *fatjetPt_b1  = (TH1F*) b1->Get("fatjetPt");
	TH1F *fatjetM_b1   = (TH1F*) b1->Get("fatjetMass");
	TH1F *fatjetEta_b1 = (TH1F*) b1->Get("fatjetEta");

	TFile* b2 = new TFile("output_BKG_WZToLNu2Q_LO_MLM_cut3.root", "r");
	TH1F *fatjetPt_b2  = (TH1F*) b2->Get("fatjetPt");
	TH1F *fatjetM_b2   = (TH1F*) b2->Get("fatjetMass");
	TH1F *fatjetEta_b2 = (TH1F*) b2->Get("fatjetEta");

	TFile* b3 = new TFile("output_BKG_WZToL3Nu_LO_MLM_cut3.root", "r");
	TH1F *fatjetPt_b3  = (TH1F*) b3->Get("fatjetPt");
	TH1F *fatjetM_b3   = (TH1F*) b3->Get("fatjetMass");
	TH1F *fatjetEta_b3 = (TH1F*) b3->Get("fatjetEta");

	TFile* b4 = new TFile("output_BKG_WWToLNu2Q_4f_LO_MLM_cut3.root", "r");
	TH1F *fatjetPt_b4  = (TH1F*) b4->Get("fatjetPt");
	TH1F *fatjetM_b4   = (TH1F*) b4->Get("fatjetMass");
	TH1F *fatjetEta_b4 = (TH1F*) b4->Get("fatjetEta");

	TFile* b5 = new TFile("output_BKG_WJetsToLNu_LO_MLM_cut3.root", "r");
	TH1F *fatjetPt_b5  = (TH1F*) b5->Get("fatjetPt");
	TH1F *fatjetM_b5   = (TH1F*) b5->Get("fatjetMass");
	TH1F *fatjetEta_b5 = (TH1F*) b5->Get("fatjetEta");

	TFile* b6 = new TFile("output_BKG_ST_s-channel_4f_leptonDecays_LO_cut3.root", "r");
	TH1F *fatjetPt_b6  = (TH1F*) b6->Get("fatjetPt");
	TH1F *fatjetM_b6   = (TH1F*) b6->Get("fatjetMass");
	TH1F *fatjetEta_b6 = (TH1F*) b6->Get("fatjetEta");

	TFile* b7 = new TFile("output_BKG_ST_t-channel_4f_inclusiveDecays_LO_cut3.root", "r");
	TH1F *fatjetPt_b7  = (TH1F*) b7->Get("fatjetPt");
	TH1F *fatjetM_b7   = (TH1F*) b7->Get("fatjetMass");
	TH1F *fatjetEta_b7 = (TH1F*) b7->Get("fatjetEta");

	TFile* b8 = new TFile("output_BKG_WH_HToBB_WToLNu.root", "r");
	TH1F *fatjetPt_b8  = (TH1F*) b8->Get("fatjetPt");
	TH1F *fatjetM_b8   = (TH1F*) b8->Get("fatjetMass");
	TH1F *fatjetEta_b8 = (TH1F*) b8->Get("fatjetEta");
	
    //Graph option

	fatjetPt_s2->SetStats(0);
	fatjetPt_s2->SetTitle(" ");
    fatjetPt_s2->GetXaxis()->SetTitle("jet P_{t} (GeV)");
	fatjetPt_s2->GetYaxis()->SetTitleOffset(1.1);
	fatjetPt_s2->GetYaxis()->SetTitle("Events");
	fatjetPt_s2->GetYaxis()->SetTitleOffset(1.2);
	fatjetPt_s2->GetXaxis()->SetLimits(199.5, 1600.);

	fatjetPt_s1->SetLineWidth(2);
	fatjetPt_s2->SetLineWidth(2);
	fatjetPt_b1->SetLineWidth(2);
	fatjetPt_b2->SetLineWidth(2);
	fatjetPt_b3->SetLineWidth(2);
	fatjetPt_b4->SetLineWidth(2);
	fatjetPt_b5->SetLineWidth(2);
	fatjetPt_b6->SetLineWidth(2);
	fatjetPt_b7->SetLineWidth(2);
	fatjetPt_b8->SetLineWidth(2);

	fatjetPt_s1->SetLineColor(9);
	fatjetPt_s1->SetFillColor(9);
	fatjetPt_s2->SetLineColor(38);
    fatjetPt_b1->SetLineColor(2);
    fatjetPt_b2->SetLineColor(8);
    fatjetPt_b3->SetLineColor(28);
    fatjetPt_b4->SetLineColor(12);
    fatjetPt_b5->SetLineColor(92);
	fatjetPt_b6->SetLineColor(87);
	fatjetPt_b7->SetLineColor(29);
	fatjetPt_b8->SetLineColor(46);
	fatjetPt_b8->SetFillColor(46);

	//Show events

	int N_fatjetPt_s1 = fatjetPt_s1->Integral();  
	int N_fatjetPt_s2 = fatjetPt_s2->Integral();
	int N_fatjetPt_b1 = fatjetPt_b1->Integral();                    
	int N_fatjetPt_b2 = fatjetPt_b2->Integral();                    
	int N_fatjetPt_b3 = fatjetPt_b3->Integral();                    
	int N_fatjetPt_b4 = fatjetPt_b4->Integral();                    
	int N_fatjetPt_b5 = fatjetPt_b5->Integral();                    
	int N_fatjetPt_b6 = fatjetPt_b6->Integral();                    
	int N_fatjetPt_b7 = fatjetPt_b7->Integral();                    
	int N_fatjetPt_b8 = fatjetPt_b8->Integral();                    
	                                                        
	cout << "The event number of s1: " << N_fatjetPt_s1 << endl;
	cout << "The event number of s2: " << N_fatjetPt_s2 << endl;
	cout << "The event number of b1: " << N_fatjetPt_b1 << endl;
	cout << "The event number of b2: " << N_fatjetPt_b2 << endl;
	cout << "The event number of b3: " << N_fatjetPt_b3 << endl;
	cout << "The event number of b4: " << N_fatjetPt_b4 << endl;
	cout << "The event number of b5: " << N_fatjetPt_b5 << endl;
	cout << "The event number of b6: " << N_fatjetPt_b6 << endl;
	cout << "The event number of b7: " << N_fatjetPt_b7 << endl;
	cout << "The event number of b8: " << N_fatjetPt_b8 << endl;

	//Normailize
		
	fatjetPt_s1->Scale(0.66407);
	fatjetPt_s2->Scale(0.33526);
	fatjetPt_b1->Scale(8.6525);
	fatjetPt_b2->Scale(1032.4); 
	fatjetPt_b3->Scale(109.26); 
	fatjetPt_b4->Scale(275.19); 
	fatjetPt_b5->Scale(4468700.);  
	fatjetPt_b6->Scale(237500.); 
	fatjetPt_b7->Scale(3940.2); 
	fatjetPt_b8->Scale(77.227);  
	
	// Draw option, make plot
	
	c1->SetLogy();                 
	fatjetPt_s2->SetMinimum(1);   
	fatjetPt_s2->SetMaximum(1000000000000);

	      
	fatjetPt_s2->Draw();
	//fatjetPt_s1->Draw("same");
	fatjetPt_b1->Draw("same");
	fatjetPt_b2->Draw("same");
	fatjetPt_b3->Draw("same");
	fatjetPt_b4->Draw("same");
	fatjetPt_b5->Draw("same");
	fatjetPt_b6->Draw("same");
	fatjetPt_b7->Draw("same");
	fatjetPt_b8->Draw("same");
	fatjetPt_s1->Draw("same");

	// legend option
	
	leg3->SetHeader("M_{Z'}/M_{W'}= 3TeV ");
	leg3->SetNColumns(2);
	leg3->AddEntry(fatjetPt_s1, "W'> WH(bb)");
	leg3->AddEntry(fatjetPt_s2, "W'> WZ(jj)");
	leg3->AddEntry(fatjetPt_b1, "tt~ > WZj");
	leg3->AddEntry(fatjetPt_b2, "WZ > LNu2Q");
	leg3->AddEntry(fatjetPt_b3, "WZ > L3Nu");
	leg3->AddEntry(fatjetPt_b4, "WW > LNu2Q");
	leg3->AddEntry(fatjetPt_b5, "Wj > LNu");
	leg3->AddEntry(fatjetPt_b6, "ST s-channel");
	leg3->AddEntry(fatjetPt_b7, "ST t-channel");
	leg3->AddEntry(fatjetPt_b8, "WH > LNubb");

	leg3->SetTextSize(0.03);
	leg4->SetHeader("g_{v}=4, c_{H}=-1, c_{F}=1");
	leg4->SetTextSize(0.02);                      
	                                              
	leg3->Draw();                                 
	leg4->Draw();                                 
}
