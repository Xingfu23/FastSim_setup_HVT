void draw_delta_phi_lepton_missingEt(){

	auto c1 = new TCanvas("c1","c1",800,600);
	auto leg3 = new TLegend(0.7, 0.7, 0.90, 0.90);

	TFile* s1 = new TFile("output_HVT_QQToWpToNuL2b.root", "r");
	TH1F *delta_phi_lep_misE_s1 = (TH1F*) s1->Get("delta_phi_lepton_MissingEt");
	TH1F *delta_phi_jet_misE_s1 = (TH1F*) s1->Get("delta_phi_jet_MissingEt");

    TFile* b1 = new TFile("output_BKG_ttWJetToLNu_LO_MLM.root", "r");
	TH1F *delta_phi_lep_misE_b1 = (TH1F*) b1->Get("delta_phi_lepton_MissingEt");
	TH1F *delta_phi_jet_misE_b1 = (TH1F*) b1->Get("delta_phi_jet_MissingEt");
	
	TFile* b2 = new TFile("output_BKG_WZToLNu2Q_LO_MLM.root", "r");
	TH1F *delta_phi_lep_misE_b2 = (TH1F*) b2->Get("delta_phi_lepton_MissingEt");
	TH1F *delta_phi_jet_misE_b2 = (TH1F*) b2->Get("delta_phi_jet_MissingEt");
	
	TFile* b3 = new TFile("output_BKG_WZToL3Nu_LO_MLM.root", "r");
	TH1F *delta_phi_lep_misE_b3 = (TH1F*) b3->Get("delta_phi_lepton_MissingEt");
	TH1F *delta_phi_jet_misE_b3 = (TH1F*) b3->Get("delta_phi_jet_MissingEt");	

	TFile* b4 = new TFile("output_BKG_WWToLNu2Q_4f_LO_MLM.root", "r");
	TH1F *delta_phi_lep_misE_b4 = (TH1F*) b4->Get("delta_phi_lepton_MissingEt");
	TH1F *delta_phi_jet_misE_b4 = (TH1F*) b4->Get("delta_phi_jet_MissingEt");	

	TFile* b5 = new TFile("output_BKG_WJetsToLNu_LO_MLM.root", "r");
	TH1F *delta_phi_lep_misE_b5 = (TH1F*) b5->Get("delta_phi_lepton_MissingEt");
	TH1F *delta_phi_jet_misE_b5 = (TH1F*) b5->Get("delta_phi_jet_MissingEt");
	
	TFile* b6 = new TFile("output_BKG_ST_s-channel_4f_leptonDecays_LO.root", "r");
	TH1F *delta_phi_lep_misE_b6 = (TH1F*) b6->Get("delta_phi_lepton_MissingEt");
	TH1F *delta_phi_jet_misE_b6 = (TH1F*) b6->Get("delta_phi_jet_MissingEt");

	TFile* b7 = new TFile("output_BKG_ST_t-channel_4f_inclusiveDecays_LO.root", "r");
	TH1F *delta_phi_lep_misE_b7 = (TH1F*) b7->Get("delta_phi_lepton_MissingEt");
	TH1F *delta_phi_jet_misE_b7 = (TH1F*) b7->Get("delta_phi_jet_MissingEt");
	
    //Graph option
	delta_phi_lep_misE_s1->SetStats(0);
	delta_phi_lep_misE_s1->SetTitle(" ");
    delta_phi_lep_misE_s1->GetXaxis()->SetTitle("delta_phi");
	delta_phi_lep_misE_s1->GetYaxis()->SetTitle("Events");
	delta_phi_lep_misE_s1->GetYaxis()->SetTitleOffset(1.4);
	delta_phi_lep_misE_s1->SetMaximum(4000.);
	delta_phi_lep_misE_s1->GetXaxis()->SetLimits(0., 10.);

	delta_phi_lep_misE_s1->SetLineWidth(2);
	delta_phi_lep_misE_b1->SetLineWidth(2);
	delta_phi_lep_misE_b2->SetLineWidth(2);
	delta_phi_lep_misE_b3->SetLineWidth(2);
	delta_phi_lep_misE_b4->SetLineWidth(2);
	delta_phi_lep_misE_b5->SetLineWidth(2);
	delta_phi_lep_misE_b6->SetLineWidth(2);
	delta_phi_lep_misE_b7->SetLineWidth(2);

	delta_phi_lep_misE_s1->SetLineColor(9);
	delta_phi_lep_misE_s1->SetFillColor(9);
    delta_phi_lep_misE_b1->SetLineColor(2);
    delta_phi_lep_misE_b2->SetLineColor(8);
    delta_phi_lep_misE_b3->SetLineColor(28);
    delta_phi_lep_misE_b4->SetLineColor(12);
    delta_phi_lep_misE_b5->SetLineColor(92);
	delta_phi_lep_misE_b6->SetLineColor(87);
	delta_phi_lep_misE_b7->SetLineColor(29);
    
	delta_phi_lep_misE_s1->Draw();
	delta_phi_lep_misE_b1->Draw("same");
	delta_phi_lep_misE_b2->Draw("same");
	delta_phi_lep_misE_b3->Draw("same");
	delta_phi_lep_misE_b4->Draw("same");
	delta_phi_lep_misE_b5->Draw("same");
	delta_phi_lep_misE_b6->Draw("same");
	delta_phi_lep_misE_b7->Draw("same");


	// legend option
	
	leg3->SetHeader("M_{Z'}/M_{W'}=2TeV, 20000 events");
	leg3->AddEntry(delta_phi_lep_misE_s1, "W'> WH(bb)");
	leg3->AddEntry(delta_phi_lep_misE_b1, "tt~ > WZj");
	leg3->AddEntry(delta_phi_lep_misE_b2, "WZ > LNu2Q");
	leg3->AddEntry(delta_phi_lep_misE_b3, "WZ > L3Nu");
	leg3->AddEntry(delta_phi_lep_misE_b4, "WW > LNu2Q");
	leg3->AddEntry(delta_phi_lep_misE_b5, "Wj > LNu");
	leg3->AddEntry(delta_phi_lep_misE_b6, "ST s-channel");
	leg3->AddEntry(delta_phi_lep_misE_b7, "ST t-channel");

	leg3->SetTextSize(0.02);

	leg3->Draw();
}

